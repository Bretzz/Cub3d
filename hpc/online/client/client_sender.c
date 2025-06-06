/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_sender.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:51:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/06 15:21:56 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "client.h"

static void	staitc_mutex_init(pthread_mutex_t *mutex)
{
	pthread_mutex_t	dead;
	static int		shield;

	ft_memset(&dead, 0, sizeof(pthread_mutex_t));
	if (shield == 0 && !ft_memcmp(mutex, &dead, sizeof(pthread_mutex_t)))
	{
		pthread_mutex_init(mutex, NULL);
		shield = 1;
	}
}

/* -1 error, 0 ok */
/* if servfd = -1, destroy the mutex */
/* !!! NEED MUTEX !!! */
/* LOBBY MUTEX */
int	client_sender(int servfd, void *buffer, size_t size)
{
	t_player *const			lobby = lbb_get_ptr(NULL);
	static pthread_mutex_t	mutex;

	staitc_mutex_init(&mutex);
	if (servfd < 0)
	{
		pthread_mutex_destroy(&mutex);
		return (0);
	}
	// if (parse_msg_string(buffer) != 2)
	// 	ft_printf(YELLOW"sending '%s' to server%s\n", buffer, RESET);
	pthread_mutex_lock(&mutex);
	lbb_mutex(1);
	if (sendto(servfd, buffer, size, 0, lobby[HOST].online, sizeof(struct sockaddr)) < 0)
	{
		ft_perror(ERROR"send failure"RESET);
		return (lbb_mutex(2), pthread_mutex_unlock(&mutex), -1);
	}
	return (lbb_mutex(2), pthread_mutex_unlock(&mutex), 0);
}
