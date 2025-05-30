/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:00:18 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/30 19:06:49 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"

#define INIT 0
#define LOCK 1
#define UNLOCK 2
#define DESTROY 3

/* static mutex for the lobby structure.
	0: INIT,
	1: LOCK,
	2: UNLOCK,
	3: DESTROY. */
void	*hpc_mutex(int action)
{
	static pthread_mutex_t	mutex;
	static int				shield;

	if (!shield && action == INIT)
	{
		ft_printf(GREEN"hpc_mutex: %p%s\n", &mutex, RESET);
		pthread_mutex_init(&mutex, NULL);
		shield = 1;
	}
	else if (shield && action == LOCK)
		pthread_mutex_lock(&mutex);
	else if (shield && action == UNLOCK)
		pthread_mutex_unlock(&mutex);
	else if (shield && action == DESTROY)
	{
		pthread_mutex_destroy(&mutex);
		shield = 0;
	}
	return (&mutex);
}
