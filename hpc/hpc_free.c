/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:29:08 by totommi           #+#    #+#             */
/*   Updated: 2025/06/07 10:21:42 by topiana-         ###   ########.fr       */
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

/* takes the socket pointer and the index pointers.
Performs all the closure routines:
	>shutting down and closing the socket (rough)
	>joins the online thread
	>destroys all mutexed (lbb, hpc, server_sender, client_sender)
	>delets the lobby. */
int	hpc_free(int *socket, int *index, unsigned long thread)
{
	const pthread_t	tid = (pthread_t)thread;

	if (index != NULL)
		safewrite(index, -1);
	if (socket != NULL)
	{
		hpc_mutex(1);
		shutdown(*socket, SHUT_RDWR);
		close(*socket);
		hpc_mutex(2);
	}
	if (tid && pthread_join(tid, NULL) != 0)
		ft_printfd(2, "Error: join online thread\n");
	server_sender(-1, NULL, NULL, 0);
	client_sender(-1, NULL, 0);
	lbb_mutex(3);
	hpc_mutex(3);
	lbb_delete_lobby((lbb_get_ptr(NULL)));
	return (0);
}
