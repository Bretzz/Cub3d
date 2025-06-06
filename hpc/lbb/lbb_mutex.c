/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:08:48 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/06 17:50:07 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"
#include "libft.h"
#include <pthread.h>

#define INIT 0
#define LOCK 1
#define UNLOCK 2
#define DESTROY 3

/* static mutex for the lobby structure.
	0: INIT,
	1: LOCK,
	2: UNLOCK,
	3: DESTROY. */
void	*lbb_mutex(int action)
{
	static pthread_mutex_t	mutex;
	static int				shield;

	if (!shield && action == INIT)
	{
		ft_printf(GREEN"lbb_mutex: %p%s\n", &mutex, RESET);
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
