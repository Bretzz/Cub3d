/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_reciever.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:42:13 by totommi           #+#    #+#             */
/*   Updated: 2025/05/31 17:14:44 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "server.h"
#include <pthread.h>

int	server_reciever(pthread_t *tid, int socket);

/* 0 error, 1 ok */ /* rn no selective ban on sussy behaviour */
int	who_is_there(int socket, t_player *lobby, struct sockaddr_in *addr, char *buffer)
{
	struct sockaddr_in	*personal;
	char				bluffer[MAXLINE + 1];

	// checking for corrupted message
	if (parse_msg_string(buffer) <= 0)
	{
		ft_printfd(STDERR_FILENO, ERROR"ack failed:%s currupted message\n", RESET);
		return (0);
	}
	
	// changing addr port and sending it to the new player
	buffer_lobby_action(lobby, "new", bluffer);
	// addr->sin_port = htons ( PORT_2 );

	ft_printf(PURPLE);
	if (server_sender(socket, bluffer, addr, 1) < 0)
		return (0);
	ft_printf(RESET);

	// storing addr in dynamic sockaddr
	personal = malloc(sizeof(struct sockaddr_in));
	if (personal == 0)
	{
		ft_perror(ERROR"malloc failure"RESET);
		return (0);
	}
	ft_memcpy(personal, addr, sizeof(struct sockaddr_in));

	// adding new player to database
	if (one_player_action(buffer, lobby, personal) <= 0)
	{
		ft_perror(ERROR"lobby failure"RESET);
		return (free(personal), 0);
	}
	// sending the update to the rest of the lobby
	if (server_sender(socket, buffer, NULL, 0) < 0)
		return (free(personal), 0);
	return (1);
}

/* checks weather the address is already in the lobby */
/* LOBBY MUTEX */
int	addr_in_lobby(t_player *lobby, struct sockaddr_in *addr)
{
	int	i;

	lbb_mutex(1);
	i = 1;
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(lobby[i]) && lobby[i].online
			&& !ft_memcmp(lobby[i].online, addr,
					sizeof(struct sockaddr_in)))
			{
				return (lbb_mutex(2), 1);
			}
		i++;
	}
	lbb_mutex(2);
	return (0);
}

/* This is awesome.
Need more parsing on what was sent?
	--> parse_msg_string()
Need different handshake provedure?
	--> who_is_there()
Need new msg interpretation?
	--> one_player_action() */
static void	*reciever(void *arg)
{
	t_player *const		lobby = lbb_get_ptr(NULL);
	char				buffer[MAXLINE + 1];
	struct sockaddr_in	addr;
	socklen_t			len;
	int					socket;
	int					parse;

	socket = *(int *)arg;
	ft_printf(LOG">recieving on socket %d%s\n", socket, RESET);
	while (!0)
	{
		len = sizeof(addr);
		ft_memset(&addr, 0, sizeof(addr));
		ft_memset(buffer, 0, sizeof(buffer));
		if (recvfrom(socket, buffer, MAXLINE, 0, (struct sockaddr *)&addr, &len) < 0)
		{
			ft_perror(ERROR"recvfrom failed"RESET);
			break;
		}
		parse = parse_msg_string(buffer);
		if (parse <= 0)
		{
			ft_printfd(STDERR_FILENO, WARN"corrupted buffer:%s '%s'\n", RESET, buffer);
			continue ;
		}
		if (parse != 2)
			ft_printf(YELLOW"%d bytes: '%s' from Client\n"RESET, ft_strlen(buffer), buffer);
		if (parse == 1
			&& !addr_in_lobby(lobby, &addr)
			&& who_is_there(socket, lobby, &addr, buffer))
			ft_printf(CONNECT"'%z' joined the game%s\n", buffer, msg_name_length(buffer), RESET);
		else if (!cycle_player_msgs(buffer, lobby))
		{
			ft_perror(ERROR"handler failure"RESET);
			break ;
		}
		// sending the update to the rest of the lobby
		if (server_sender(socket, buffer, &addr, 0) < 0)
			break ;
	}
	return (close(socket), free(arg), NULL);
}
// if (handle_client_players(buffer, recenv) < 0)
// {
// 	ft_printf(HOSTLOG"A NEW HOST WILL RISE%s\n", RESET);
// 	return (close(recenv->player[0].socket), free(recenv), NULL);
// }

/* Spawns a thread that listen to the everyone
and handles new connections. */
int	server_reciever(pthread_t *tid, int socket)
{
	int	*const my_socket = malloc(1 * sizeof(int));
	
	if (my_socket == NULL)
		return (-1);
	// ft_printf("sus2 %p\n", &socket);
	*my_socket = socket;
	if (pthread_create(tid, NULL, &reciever, my_socket) < 0)
	{
		ft_perror(ERROR"reciever launch failed"RESET);
		return (-1);
	}
	// if (code != 0)
	// {
	// 	ft_printfd(STDERR_FILENO, ERROR"detach failure:%s code %d\n", RESET, code);
	// 	return (-1);
	// }
	return (0);
}
