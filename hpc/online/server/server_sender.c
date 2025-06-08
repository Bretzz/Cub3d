/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sender.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:14:57 by totommi           #+#    #+#             */
/*   Updated: 2025/06/08 16:22:49 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "server.h"

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
static int	private_send(int socket,
	char *buffer, void *addr, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (sendto(socket, buffer, ft_strlen(buffer), 0,
			addr, sizeof(struct sockaddr)) < 0)
	{
		ft_perror(ERROR"sendto failure"RESET);
		return (pthread_mutex_unlock(mutex), -1);
	}
	return (pthread_mutex_unlock(mutex), 0);
}

static int	public_send(int socket,
	char *buffer, void *addr, pthread_mutex_t *mutex)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	int				i;

	i = 1;
	pthread_mutex_lock(mutex);
	lbb_mutex(1);
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(lobby[i]) && lobby[i].online != NULL
			&& (addr == NULL
				|| ft_memcmp(lobby[i].online, addr, sizeof(struct sockaddr_in)))
			&& sendto(socket, buffer, ft_strlen(buffer), 0,
				lobby[i].online, sizeof(struct sockaddr)) < 0)
		{
			ft_perror(ERROR"sendto failure"RESET);
			return (lbb_mutex(2), pthread_mutex_unlock(mutex), -1);
		}
		i++;
	}
	return (lbb_mutex(2), pthread_mutex_unlock(mutex), 0);
}

/* -1 error, 0 ok */
/* socket and message to send,
if flag == 1 send to addr,
if flag == 0 send to everyone BUT addr.
if socket == -1, desroy the mutex. */
/* NOTE: case addr = NULL:
	flag 1, error,
	flag 0, send to all.  */
int	server_sender(int socket, char *buffer, void *addr, char flag)
{
	static pthread_mutex_t	mutex;

	staitc_mutex_init(&mutex);
	if (socket < 0 && !pthread_mutex_destroy(&mutex))
		return (0);
	if (DEBUG && parse_msg_string(buffer) != 2)
		ft_printf(YELLOW"sending '%s' on \
socket %d%s\n", (char *)buffer, socket, RESET);
	if (flag == 1)
	{
		if (private_send(socket, buffer, addr, &mutex) < 0)
			return (-1);
	}
	else if (flag == 0 && lbb_get_ptr(NULL) == NULL)
	{
		ft_printfd(STDERR_FILENO, ERROR"sender \
failure:%s lobby not initialized\n", RESET);
		return (-1);
	}
	else if (flag == 0)
	{
		if (public_send(socket, buffer, addr, &mutex) < 0)
			return (-1);
	}
	return (0);
}
