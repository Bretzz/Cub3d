/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_me_online.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:15:22 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/06 15:06:59 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "online.h"

static void safewrite(int *socket, int *index, int *socket_index)
{
	hpc_mutex(1);
	*socket = socket_index[0];
	*index = socket_index[1];
	hpc_mutex(2);
}

static void saferead(int *socket, int *index, int *socket_index)
{
	// hpc_mutex(1);
	socket_index[0] = *socket;
	socket_index[1] = *index;
	// hpc_mutex(2);
}

static void	*manager(void *arg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	t_setup *const	setup = arg;
	pthread_t		tid;
	int				code;
	int				socket_index[2];

	// ft_printf("stack:\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n", &manager, &arg, &lobby, &setup, &tid, &code, &socket_index, &socket_index[1]);

	saferead(setup->socket, setup->index, socket_index);
	while (!0)
	{
		safewrite(setup->socket, setup->index, socket_index);
		safeclose(socket_index[0]);
		tid = 0;
		if (socket_index[1] == HOST)
		{
			usleep(1000);	//needed for the second rerout
			ft_printf(LOG"===STARTING SERVER===\n"RESET);
			socket_index[0] = server_routine(&tid, setup->envp);
		}
		else if (socket_index[1] == PLAYER)
		{
			usleep(1000);	//needed for the second rerout
			ft_printf(LOG"===STARTING CLIENT===\n"RESET);
			socket_index[0] = client_routine(&tid, setup->envp);
		}
		if (tid == 0 || socket_index[0] < 0)	// signal minigame that online crashed???
			break ;
		safewrite(setup->socket, setup->index, socket_index);	// dangerous
		code = pthread_join(tid, NULL);
		if (code != 0)
		{
			ft_printfd(STDERR_FILENO, ERROR"online join failure:%s code %d\n", RESET, code);
			hpc_mutex(1);
			*setup->index = -1;
			hpc_mutex(2);
			break ;
		}
		ft_printf(LOG">reciever closed%s\n", RESET);
		if (hpc_mutex(1) && *setup->index < 0 && hpc_mutex(2))	// we died (-1 set in minigame)
			break ;
		hpc_mutex(2);
		/* LOBBY MUTEX */
		lbb_mutex(1);
		if (!ft_strcmp(get_locl_ip(setup->envp), lobby[HOST].ip)
			&& !ft_strcmp(get_my_name(setup->envp), lobby[HOST].name))
			socket_index[1] = HOST;
		else
			make_him_host(lobby[HOST].ip, setup->envp);	//could break
		lbb_mutex(2);
	}
	// ft_printf("manager out\n");
	return (safeclose(socket_index[0]), free_fake_env(setup->envp), free(setup), NULL);
}

/* initialize variables based on data */
static int	data_init(int *socket, int *index, char *envp[])
{
	char *const servip = get_serv_ip(envp);

	if (!socket || !index || !envp)
		return (0);
	*socket = 0;
	if (!ft_strcmp("host", servip))
		*index = 0;
	else if (is_ip(servip))
		*index = 1;
	else
		return (0);
	return (1);
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
		3.1 we died? return : go to 1
NOTE: the 'envp' will be free'd as a custom matrix pointer,
meaning evey single 'sring' will be individually free'd, before
freeint the 'envp' pointer itself. */
pthread_t	get_me_online(int *index, int *socket, char *envp[])
{
	pthread_t	tid;
	t_setup		*setup;

	// ft_printf("before stack:\n%p\n%p\n", &tid, &setup);

	set_my_ip(get_my_addr(), envp);
	if (!env_is_ready(envp))
		return ((pthread_t)0);
	setup = malloc(sizeof(t_setup));
	if (setup == NULL)
		return ((pthread_t)0);
	setup->index = index;
	setup->socket = socket;
	setup->envp = envp;
	if (!data_init(socket, index, envp))
		return (free(setup), (pthread_t)0);
	if (pthread_create(&tid, NULL, &manager, setup) < 0)
	{
		ft_perror(ERROR"thread launch"RESET);
		return (free(setup), (pthread_t)0);
	}
	while (hpc_mutex(1) && *socket == 0 && hpc_mutex(2))
		usleep(1000);
	return (hpc_mutex(2), tid);
}
