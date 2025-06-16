/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_ack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:31:48 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/11 13:56:32 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "server.h"

/* checks weather the address is already in the lobby */
/* LOBBY MUTEX */
static int	addr_in_lobby(t_player *lobby, struct sockaddr_in *addr)
{
	int	i;

	lbb_mutex(1);
	i = 1;
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(lobby[i]) && lobby[i].online
			&& !ft_memcmp(lobby[i].online, addr,
				sizeof(struct sockaddr_in)))
			return (lbb_mutex(2), 1);
		i++;
	}
	lbb_mutex(2);
	return (0);
}

/* sending the whole lobby's data to the client
-1 fail, 0 continue */
static int	send_test(int socket, t_player *lobby, struct sockaddr_in *addr)
{
	char	bluffer[MAXLINE + 1];

	ft_memset(bluffer, 0, sizeof(bluffer));
	buffer_lobby_action(lobby, "new", bluffer);
	if (server_sender(socket, bluffer, addr, 1) < 0)
		return (-1);
	return (0);
}

/* adds the new address to the '.online' field
of the player slot in the lobby
-1 error, 0 ok */
static int	add_client_addr(t_player *lobby,
		struct sockaddr_in *addr, char *buffer)
{
	struct sockaddr_in	*personal;

	personal = malloc(sizeof(struct sockaddr_in));
	if (personal == NULL)
	{
		ft_perror(ERROR"malloc failure"RESET);
		return (-1);
	}
	ft_memcpy(personal, addr, sizeof(struct sockaddr_in));
	if (one_player_action(buffer, lobby, personal) <= 0)
	{
		ft_perror(ERROR"lobby failure"RESET);
		return (free(personal), -1);
	}
	return (0);
}

/* sends to the whole lobby the msg sent by the client
(announcing himself). If the send goes wrong tells the
client to kill himself (xD)
-1 error, 0 ok */
static int	send_lobby(int socket, struct sockaddr_in *addr, char *buffer)
{
	char	killbuff[MAXLINE + 1];

	if (server_sender(socket, buffer, addr, 0) < 0)
	{
		ft_memset(killbuff, 0, sizeof(killbuff));
		ft_strlcpy(killbuff, buffer, ft_strlen(buffer));
		ft_memmove(killbuff + (ft_strlen(killbuff) - 2), "kill", 5);
		server_sender(socket, killbuff, addr, 1);
		return (-1);
	}
	return (0);
}

/* 0 error, 1 ok */ /* rn no selective ban on sussy behaviour */
int	server_ack(int socket, t_player *lobby,
	struct sockaddr_in *addr, char *buffer)
{
	if (parse_msg_string(buffer) <= 0)
	{
		ft_printfd(STDERR_FILENO, ERROR"ack failed:%s \
currupted message\n", RESET);
		return (0);
	}
	if (addr_in_lobby(lobby, addr))
		return (0);
	if (send_test(socket, lobby, addr) < 0)
		return (0);
	if (add_client_addr(lobby, addr, buffer) < 0)
		return (0);
	if (send_lobby(socket, addr, buffer) < 0)
		return (0);
	if (DEBUG)
		ft_printf(WARN"implement ':renew' action on \
'send_lobby' failure (server_ack)%s\n", RESET);
	return (1);
}
