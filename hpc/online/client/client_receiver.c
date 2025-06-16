/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_receiver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:33:11 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/11 02:16:45 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "client.h"

int	client_receiver(pthread_t *tid, int servfd);

/* recvfrom function called, checks for corrypted buffers or
empty buffers (socket closed with 'close(3)')
-1 break, 0 ok */
static int	receive_buffer(int servfd, char *buffer)
{
	int	len;
	int	parse;

	ft_memset(buffer, 0, (MAXLINE + 1) * sizeof(char));
	len = recvfrom(servfd, buffer, MAXLINE, 0, NULL, 0);
	if (len < 0)
	{
		ft_perror(ERROR"recvfrom failed"RESET);
		return (-1);
	}
	else if (len == 0)
		return (-1);
	parse = parse_msg_string(buffer);
	if (parse <= 0)
	{
		ft_printfd(STDERR_FILENO, WARN"corrupted \
buffer:%s '%s'\n", RESET, buffer);
		return (-1);
	}
	if (DEBUG && parse != 2)
		ft_printf(YELLOW"%d bytes: '%s' from Server\n"RESET, len, buffer);
	return (parse);
}

/* -1 break, 0 ok */
static int	process_buffer(t_player *lobby, char *buffer)
{
	const int	parse = parse_msg_string(buffer);

	if (!cycle_player_msgs(buffer, lobby))
	{
		ft_perror(ERROR"handler failure"RESET);
		return (-1);
	}
	if (parse == 4 || parse == 7)
		return (-1);
	return (0);
}

static void	*receiver(void *arg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	char			buffer[MAXLINE + 1];
	int				servfd;

	servfd = *(int *)arg;
	if (DEBUG)
		ft_printf(LOG">receiving on socket %d%s\n", servfd, RESET);
	while (!0)
	{
		if (receive_buffer(servfd, buffer) < 0)
			break ;
		if (process_buffer(lobby, buffer) < 0)
			break ;
	}
	close(servfd);
	return (free(arg), NULL);
}

/* Spawns a thread that listen to the server for updates on the players */
int	client_receiver(pthread_t *tid, int servfd)
{
	int *const	my_servfd = malloc(1 * sizeof(int));

	if (my_servfd == NULL)
		return (-1);
	*my_servfd = servfd;
	if (pthread_create(tid, NULL, &receiver, my_servfd) < 0)
	{
		ft_perror(ERROR"receiver launch failed"RESET);
		return (-1);
	}
	return (0);
}
