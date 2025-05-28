/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:29:08 by totommi           #+#    #+#             */
/*   Updated: 2025/05/21 00:56:05 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include <pthread.h>

int	hpc_free(int *socket, int *index, void *thread);

/* takes the socket pointer and the index pointers.
Performs all the closure routines. */
int	hpc_free(int *socket, int *index, void *thread)
{
	const pthread_t	tid = *(pthread_t *)thread;

	// shutting down the 'online' thread
	*index = -1; // signal that we got killed in game
	// usleep(100);
	// shutdown(*mlx->socket, SHUT_RDWR);	// add for cleaner resoult(?)
	close(*socket);	// gets the threads out of the syscall
	// waits the thread
	if (tid && pthread_join(tid, NULL) != 0) { /* throw error */ }
	server_sender(-1, NULL, NULL, 0);	// destroying mutexes
	client_sender(-1, NULL, 0);			// destroying mutexes
	lbb_delete_lobby((lbb_get_ptr(NULL)));
	return (0);
}
