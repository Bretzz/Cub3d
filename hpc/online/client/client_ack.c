/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:26:09 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/17 20:07:20 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "client.h"

int	client_ack(int servfd, t_player *lobby);

/* logging:
	ft_printf(PURPLE"[test] sending '%s' to server%s\n", buffer, RESET); */
/* -1 error, 0 ok. */
static int	send_test(int servfd, t_player *lobby, char *buffer)
{
	ft_memset(buffer, 0, (MAXLINE + 1) * sizeof(char));
	lbb_mutex(1);
	buffer_player_action(lobby[PLAYER], "new", buffer);
	lbb_mutex(2);
	if (DEBUG)
		ft_printf(PURPLE"[test] sending '%s' to server%s\n", buffer, RESET);
	if (sendto(servfd, buffer, ft_strlen(buffer), 0,
			(struct sockaddr *)lobby[HOST].online, sizeof(struct sockaddr)) < 0)
	{
		ft_perror(ERROR"sendto failure"RESET);
		return (-1);
	}
	return (0);
}

/* -1 error, 0 ok */
static int	revc_test(int servfd, char *buffer)
{
	ft_memset(buffer, 0, (MAXLINE + 1) * sizeof(char));
	if (recvfrom(servfd, buffer, MAXLINE, 0, NULL, 0) < 0)
	{
		ft_perror(ERROR"recvfrom failed"RESET);
		return (-1);
	}
	if (DEBUG)
		ft_printf(PURPLE"[test] received '%s' from server%s\n", buffer, RESET);
	return (0);
}

/* -1 error, 0 ok */
/* right now the message sent by the server is the list
of players wi the 'new' action */
static int	validation(t_player *lobby, char *buffer)
{
	if (!cycle_player_msgs(buffer, lobby))
	{
		ft_perror(ERROR"execute failure"RESET);
		return (-1);
	}
	if (DEBUG)
		ft_printf(CONNECT"connection accepted!!!%s\n", RESET);
	return (0);
}

/* writes the ack msg into the ack_data() buffer */
static int	recv_ack_msg(int servfd, char *buffer)
{
	ft_memset(buffer, 0, (MAXLINE + 1) * sizeof(char));
	if (recvfrom(servfd, buffer, MAXLINE, 0, NULL, 0) < 0)
	{
		ft_perror(ERROR"recvfrom failed"RESET);
		return (-1);
	}
	if (DEBUG)
		ft_printf(PURPLE"[ack] received '%s' from server%s\n", buffer, RESET);
	if (!cycle_player_msgs(buffer, lbb_get_ptr(NULL)))
	{
		ft_perror(ERROR"execute failure"RESET);
		return (-1);
	}
	if (DEBUG)
		ft_printf(CONNECT"[ack] data stored correctly%s\n", RESET);
	return (0);
}

/* Acknowledgment procedure with the server.
	1. send signature + new to server
	2. receive lobby stats */
/* LOBBY MUTEX */
int	client_ack(int servfd, t_player *lobby)
{
	char	buffer[MAXLINE + 1];

	if (DEBUG)
		ft_printf(LOG">ack procedure... (socket %d)%s\n", servfd, RESET);
	if (send_test(servfd, lobby, buffer) < 0)
		return (-1);
	if (revc_test(servfd, buffer) < 0)
		return (-1);
	if (validation(lobby, buffer) < 0)
		return (-1);
	if (ACK_DATA == 0)
		return (0);
	if (recv_ack_msg(servfd, buffer) < 0)
		return (-1);
	return (0);
}
