/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:29:08 by totommi           #+#    #+#             */
/*   Updated: 2025/05/28 20:12:20 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include <pthread.h>
#include <sys/socket.h>

int	hpc_free(int *socket, int *index, void *thread);

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
		*index = -1;					// signal that we got killed in game
		// usleep(100);
	if (socket != NULL)
	{
		shutdown(*socket, SHUT_RDWR);	// add for cleaner resoult(?)
		close(*socket);					// gets the threads out of the syscall
	}
	// waits the thread
	if (tid && pthread_join(tid, NULL) != 0) { /* throw error */ }
	server_sender(-1, NULL, NULL, 0);	// destroying mutexes
	client_sender(-1, NULL, 0);			// destroying mutexes
	lbb_delete_lobby((lbb_get_ptr(NULL)));
	return (0);
}
