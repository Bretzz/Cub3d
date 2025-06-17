/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:29:08 by totommi           #+#    #+#             */
/*   Updated: 2025/06/17 20:41:38 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include <pthread.h>
#include <sys/socket.h>

int	hpc_free(int *socket, int *index, unsigned long thread);

static int	saferead(int *target)
{
	int	my_value;

	hpc_mutex(1);
	my_value = *target;
	hpc_mutex(2);
	return (my_value);
}

static void	safewrite(int *target, int value)
{
	hpc_mutex(1);
	*target = value;
	hpc_mutex(2);
}

/* checks if you started 2 sessions on the same machine */
static int	multiple_local_sessions(int my_index, t_player *lobby)
{
	int	index;

	index = 0;
	while (index < MAXPLAYERS)
	{
		if (lbb_is_alive(lobby[index]) && index != my_index
			&& !ft_strcmp(lobby[my_index].ip, lobby[index].ip))
			return (1);
		index++;
	}
	return (0);
}

/* tryes to shutdown the online thread safely
all these wrapped in hpc and lbb mutex pls.
RETURNS: 1: clean procedure, 0: forced procdure. */
static int	shutdown_procedure(int *socket, int *index, t_player *lobby)
{
	char		buffer[MSG_LEN + 9];
	const int	my_index = saferead(index);

	safewrite(index, -1);
	if (saferead(socket) <= 2)
		return (0);
	hpc_mutex(1);
	lbb_mutex(1);
	if (lobby[my_index].online != NULL
		&& !multiple_local_sessions(my_index, lobby))
	{
		ft_memset(buffer, 0, sizeof(buffer));
		ft_strlcpy(buffer, "pls:just:die:fast:shutdown", sizeof(buffer));
		if (sendto(*socket, buffer, sizeof(buffer), 0,
				lobby[my_index].online, sizeof(struct sockaddr)) < 0)
		{
			ft_perror(ERROR"send failure"RESET);
			return (shutdown(*socket, SHUT_RDWR), close(*socket),
				lbb_mutex(2), hpc_mutex(2), 0);
		}
	}
	else
		return (shutdown(*socket, SHUT_RDWR), close(*socket),
			lbb_mutex(2), hpc_mutex(2), 0);
	return (lbb_mutex(2), hpc_mutex(2), 1);
}

/* takes the socket pointer and the index pointers.
Performs all the closure routines:
	>shutting down and closing the socket (rough)
	>joins the online thread
	>destroys all mutexed (lbb, hpc, server_sender, client_sender)
	>delets the lobby. */
int	hpc_free(int *socket, int *index, unsigned long thread)
{
	const pthread_t	tid = (pthread_t)thread;

	if (socket != NULL && index != NULL)
		shutdown_procedure(socket, index, lbb_get_ptr(NULL));
	else if (index != NULL)
		safewrite(index, -1);
	if (tid && pthread_join(tid, NULL) != 0)
		ft_printfd(2, "Error: join online thread\n");
	server_sender(-1, NULL, NULL, 0);
	client_sender(-1, NULL, 0);
	lbb_mutex(3);
	hpc_mutex(3);
	free(*ack_data());
	lbb_delete_lobby((lbb_get_ptr(NULL)));
	return (0);
}
