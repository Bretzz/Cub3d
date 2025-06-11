/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_me_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:56:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/11 02:12:37 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "online.h"

// ft_printf(LOG"===STARTING SERVER===\n"RESET);
// ft_printf(LOG"===STARTING CLIENT===\n"RESET);
static int	select_routine(pthread_t *tid, int index, char *envp[])
{
	*tid = 0;
	if (index == HOST)
	{
		usleep(1000);
		if (DEBUG)
			ft_printf(LOG"===STARTING SERVER===\n"RESET);
		return (server_routine(tid, envp));
	}
	else if (index == PLAYER)
	{
		usleep(2000);
		if (DEBUG)
			ft_printf(LOG"===STARTING CLIENT===\n"RESET);
		return (client_routine(tid, envp));
	}
	return (-1);
}

/* checks if the host changed and updates index accordingly */
static void	lobby_update(t_player *lobby, t_setup *setup)
{
	lbb_mutex(1);
	if (!ft_strcmp(get_locl_ip(setup->envp), lobby[HOST].ip)
		&& !ft_strcmp(get_my_name(setup->envp), lobby[HOST].name))
		*setup->index = HOST;
	else
		make_him_host(lobby[HOST].ip, setup->envp);
	lbb_mutex(2);
}

/* writes the error msg, sets the index to -1 and unlocks the mutex */
static void	error_break(const char *error, int *socket)
{
	ft_printfd(STDERR_FILENO, ERROR"Error%s: %s\n", RESET, error);
	*socket = -1;
	hpc_mutex(2);
}

/* single routine cycle, assuming hpc_mutex(1) call beforehand
-1 break, 0 ok */
static int	single_routine(t_setup *setup, pthread_t *tid)
{
	safeclose(*setup->socket);
	*setup->socket = select_routine(tid, *setup->index, setup->envp);
	if (*tid == 0 || *setup->socket < 0)
	{
		error_break("online routine failure", setup->socket);
		return (-1);
	}
	hpc_mutex(2);
	if (pthread_join(*tid, NULL) != 0 && hpc_mutex(1))
	{
		safeclose(*setup->socket);
		error_break("online joine failure", setup->socket);
		return (-1);
	}
	hpc_mutex(1);
	if (DEBUG)
		ft_printf(LOG">receiver closed%s\n", RESET);
	return (0);
}

/* cycles trough: routine -> game status check -> new host check -> again... */
void	*manager(void *arg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	t_setup *const	setup = arg;
	pthread_t		tid;

	while (!0)
	{
		hpc_mutex(1);
		if (single_routine(setup, &tid) < 0)
			break ;
		if (*setup->index < 0 && hpc_mutex(2))
			break ;
		lobby_update(lobby, setup);
		hpc_mutex(2);
	}
	safeclose(*setup->socket);
	free_fake_env(setup->envp);
	free(setup);
	return (NULL);
}
