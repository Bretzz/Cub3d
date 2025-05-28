/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_me_online.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:15:22 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 00:53:25 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "online.h"

static void	*manager(void *arg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	t_setup *const	setup = arg;
	pthread_t		tid;
	int				code;

	while (!0)
	{
		if (*setup->socket > 2)
			close(*setup->socket);
		if (*setup->index == HOST)
		{
			ft_printf(LOG"===STARTING SERVER===\n"RESET);
			*setup->socket = server_routine(&tid, setup->envp);
		}
		else if (*setup->index == PLAYER)
		{
			usleep(1000);
			ft_printf(LOG"===STARTING CLIENT===\n"RESET);
			*setup->socket = client_routine(&tid, setup->envp);
		}
		if (*setup->socket < 0)
			break ;
		code = pthread_join(tid, NULL);
		if (code != 0)
		{
			ft_printfd(STDERR_FILENO, ERROR"online join failure:%s code %d\n", RESET, code);
			*setup->index = -1;
			break ;
		}
		ft_printf(LOG">reciever closed%s\n", RESET);
		if (*setup->index < 0)	// we died (-1 set in minigame)
			break ;
		if (!ft_strcmp(get_locl_ip(setup->envp), lobby[HOST].ip))
			*setup->index = HOST;
		else
			make_him_host(lobby[HOST].ip, setup->envp);	//could break
	}
	return (close(*setup->socket), free(setup), NULL);
}

/* initialize variables based on data */
static int	data_init(int *socket, int *index, char *envp[])
{
	*socket = 0;
	if (!ft_strcmp("host", get_serv_ip(envp)))
		*index = 0;
	else
		*index = 1;
	return (0);
}

/* Spawns the manager thread for internet connection.
Switches from client to host on kill, and changes host
if the host died. If the socket pointed by *socket gets
close(3)d, the thread starts the cleanup routine.
RETURNS: the thread to join before shutting down  */
/* HOW IT WORKS:
	1. reads the index,
	2. starts the routine & sets the socket
	3. (something changes)
		3.1 we died? return : go to 1 */
/* PLS INITIALIZE SOCKET */
pthread_t	get_me_online(int *index, int *socket, char *envp[])
{
	pthread_t	tid;
	t_setup		*setup;

	setup = malloc(sizeof(t_setup));
	if (setup == NULL)
		return (0);
	setup->index = index;
	setup->socket = socket;
	setup->envp = envp;
	data_init(index, socket, envp);
	if (pthread_create(&tid, NULL, &manager, setup) < 0)
	{
		ft_perror(ERROR"thread launch"RESET);
		return (0);
	}
	while (*socket == 0)
		usleep(1000);
	return (tid);
}
