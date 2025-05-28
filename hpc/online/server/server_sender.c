/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sender.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:14:57 by totommi           #+#    #+#             */
/*   Updated: 2025/05/28 22:35:51 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "server.h"

static void	staitc_mutex_init(pthread_mutex_t *mutex)
{
	pthread_mutex_t	dead;

	ft_memset(&dead, 0, sizeof(pthread_mutex_t));
	if (!ft_memcmp(mutex, &dead, sizeof(pthread_mutex_t)))
		pthread_mutex_init(mutex, NULL);
}

/* -1 error, 0 ok */
/* socket and message to send,
if flag == 1 send to addr,
if flag == 0 send to everyone BUT addr.
if socket == -1, desroy the mutex. */
/* NOTE: case addr = NULL:
	flag 1, error,
	flag 0, send to all.  */
int server_sender(int socket, char *buffer, void *addr, char flag)
{
	t_player *const			lobby = lbb_get_ptr(NULL);
	static pthread_mutex_t	mutex;
	int						i;

	if (socket < 0)
	{
		pthread_mutex_destroy(&mutex);
		return (0);
	}
	ft_printf(YELLOW"sending '%s' on socket %d%s\n", (char *)buffer, socket, RESET);
	staitc_mutex_init(&mutex);
	if (flag == 1)
	{
		pthread_mutex_lock(&mutex);
		if (sendto(socket, buffer, ft_strlen(buffer), 0, addr, sizeof(struct sockaddr)) < 0)
		{
			ft_perror(ERROR"sendto failure"RESET);
			return (pthread_mutex_unlock(&mutex), -1);
		}
		return (pthread_mutex_unlock(&mutex), 0);
	}
	if (flag == 0 && lobby == NULL)
	{
		ft_printfd(STDERR_FILENO, ERROR"sender failure:%s lobby not initialized\n", RESET);
		return (-1);
	}
	i = 1;
	pthread_mutex_lock(&mutex);
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(lobby[i]) && (!addr || ft_memcmp(lobby[i].online, addr, sizeof(struct sockaddr_in)))
			&& ft_printf("sending to %s\n", lobby[i].name)
			&& sendto(socket, buffer, ft_strlen(buffer), 0, lobby[i].online, sizeof(struct sockaddr)) < 0)
		{
			ft_perror(ERROR"sendto failure"RESET);
			return (pthread_mutex_unlock(&mutex), -1);
		}
		i++;
	}
	return (pthread_mutex_unlock(&mutex), 0);
}
