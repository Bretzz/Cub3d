/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:29:08 by totommi           #+#    #+#             */
/*   Updated: 2025/06/11 02:21:10 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include <pthread.h>
#include <sys/socket.h>

int	hpc_free(int *socket, int *index, unsigned long thread);

static void	safewrite(int *target, int value)
{
	hpc_mutex(1);
	*target = value;
	hpc_mutex(2);
}

/* tryes to shutdown the online thread safely
all these wrapped in hpc and lbb mutex pls. */
static void	shutdown_procedure(int *socket, int *index, t_player *lobby)
{
	char	buffer[MSG_LEN + 9];
	int		my_socket;
	int		my_index;

	hpc_mutex(1);
	my_socket = *socket;
	my_index = *index;
	*index = -1;
	lbb_mutex(1);
	if (lobby[my_index].online != NULL)
	{
		ft_memset(buffer, 0, sizeof(buffer));
		ft_strlcpy(buffer, "pls:just:die:fast:shutdown", sizeof(buffer));
		if (sendto(my_socket, buffer, sizeof(buffer), 0,
			lobby[my_index].online, sizeof(struct sockaddr)) < 0)
		{
			ft_perror(ERROR"send failure"RESET);
			close(*socket);
		}
	}
	else
		close(*socket);
	lbb_mutex(2);
	hpc_mutex(2);
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
	// if (socket != NULL)
	// {
	// 	hpc_mutex(1);
	// 	if (lbb_get_ptr(NULL)[*index])
	// 	shutdown(*socket, SHUT_RDWR);
	// 	close(*socket);
	// 	hpc_mutex(2);
	// }
	if (tid && pthread_join(tid, NULL) != 0)
		ft_printfd(2, "Error: join online thread\n");
	server_sender(-1, NULL, NULL, 0);
	client_sender(-1, NULL, 0);
	lbb_mutex(3);
	hpc_mutex(3);
	lbb_delete_lobby((lbb_get_ptr(NULL)));
	return (0);
}
