/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_receiver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:42:13 by totommi           #+#    #+#             */
/*   Updated: 2025/06/11 02:16:25 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "server.h"
#include <pthread.h>

int	server_receiver(pthread_t *tid, int socket);

/* recvfrom function called, checks for corrypted buffers or
empty buffers (socket closed with 'close(3)')
-1 break, 0 ok */
static int	receive_buffer(int socket, struct sockaddr_in *addr, char *buffer)
{
	socklen_t	s_len;
	int			r_len;

	s_len = sizeof(struct sockaddr_in);
	ft_memset(addr, 0, sizeof(struct sockaddr_in));
	ft_memset(buffer, 0, MAXLINE + 1);
	r_len = recvfrom(socket, buffer, MAXLINE, 0,
			(struct sockaddr *)addr, &s_len);
	if (r_len < 0)
	{
		ft_perror(ERROR"recvfrom failed"RESET);
		return (-1);
	}
	else if (r_len == 0)
		return (-1);
	return (0);
}

/* -1 break, 1 continue, 0 ok */
static int	process_buffer(int socket, struct sockaddr_in *addr, char *buffer)
{
	t_player *const		lobby = lbb_get_ptr(NULL);
	const int			parse = parse_msg_string(buffer);

	if (DEBUG && parse != 2)
		ft_printf(YELLOW"%d bytes: '%s' from \
Client\n"RESET, ft_strlen(buffer), buffer);
	if (parse == 1 && server_ack(socket, lobby, addr, buffer) && DEBUG)
		ft_printf(CONNECT"'%z' joined the \
game%s\n", buffer, msg_name_length(buffer), RESET);
	else if (parse == 7)
		return (-1);
	else if (!cycle_player_msgs(buffer, lobby))
	{
		ft_perror(ERROR"handler failure"RESET);
		return (-1);
	}
	return (0);
}

/* This is awesome.
Need more parsing on what was sent?
	--> parse_msg_string()
Need different handshake provedure?
	--> server_ack()
Need new msg interpretation?
	--> one_player_action() */
static void	*receiver(void *arg)
{
	char				buffer[MAXLINE + 1];
	struct sockaddr_in	addr;
	int					socket;

	socket = *(int *)arg;
	if (DEBUG)
		ft_printf(LOG">receiving on socket %d%s\n", socket, RESET);
	while (!0)
	{
		if (receive_buffer(socket, &addr, buffer) < 0)
			break ;
		if (parse_msg_string(buffer) <= 0)
		{
			ft_printfd(STDERR_FILENO, WARN"corrupted \
buffer:%s '%s'\n", RESET, buffer);
			continue ;
		}
		if (process_buffer(socket, &addr, buffer) < 0)
			break ;
		if (server_sender(socket, buffer, &addr, 0) < 0)
			break ;
	}
	return (close(socket), free(arg), NULL);
}

/* Spawns a thread that listen to the everyone
and handles new connections. */
int	server_receiver(pthread_t *tid, int socket)
{
	int *const	my_socket = malloc(1 * sizeof(int));

	if (my_socket == NULL)
		return (-1);
	*my_socket = socket;
	if (pthread_create(tid, NULL, &receiver, my_socket) < 0)
	{
		ft_perror(ERROR"receiver launch failed"RESET);
		return (-1);
	}
	if (DEBUG)
		ft_printf(LOG">receiver launched%s\n", RESET);
	return (0);
}
