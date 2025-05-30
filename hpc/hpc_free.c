/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:29:08 by totommi           #+#    #+#             */
/*   Updated: 2025/05/30 17:46:47 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include <pthread.h>
#include <sys/socket.h>

int	hpc_free(int *socket, int *index, void *thread);

static void safewrite(int *target, int value)
{
	hpc_mutex(1);
	*target = value;
	hpc_mutex(2);
}

/* takes the socket pointer and the index pointers.
Performs all the closure routines. */
int	hpc_free(int *socket, int *index, void *thread)
{
	pthread_t	tid;

	if (thread != NULL)
		tid = *(pthread_t *)thread;
	else
		tid = 0;

	// shutting down the 'online' thread
	if (index != NULL)
		safewrite(index, -1);
	if (socket != NULL)
	{
		hpc_mutex(1);
		shutdown(*socket, SHUT_RDWR);	// add for cleaner resoult(?)
		close(*socket);					// gets the threads out of the syscall
		hpc_mutex(2);
	}
	// waits the thread
	
	if (tid && pthread_join(tid, NULL) != 0) { /* throw error */ }
	server_sender(-1, NULL, NULL, 0);	// destroying mutexes
	client_sender(-1, NULL, 0);			// destroying mutexes
	lbb_mutex(3);						// destroying mutexes
	hpc_mutex(3);						// destroying mutexes
	lbb_delete_lobby((lbb_get_ptr(NULL)));
	return (0);
}
