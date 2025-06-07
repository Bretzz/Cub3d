/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_me_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:56:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/07 19:22:01 by topiana-         ###   ########.fr       */
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
		return (server_routine(tid, envp));
	}
	else if (index == PLAYER)
	{
		usleep(10000);
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

static void	error_break(const char *error, int *index)
{
	ft_printfd(STDERR_FILENO, ERROR"%s%s\n", error, RESET);
	*index = -1;
	hpc_mutex(2);
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
		safeclose(*setup->socket);
		*setup->socket = select_routine(&tid, *setup->index, setup->envp);
		if (tid == 0 || *setup->socket < 0)
		{
			error_break("online routine failure", setup->index);
			break ;
		}
		hpc_mutex(2);
		if (pthread_join(tid, NULL) != 0 && hpc_mutex(1))
		{
			error_break("online joine failure", setup->index);
			break ;
		}
		hpc_mutex(1);
		// ft_printf(LOG">reciever closed%s\n", RESET);
		if (*setup->index < 0 && hpc_mutex(2))
			break ;
		lobby_update(lobby, setup);
		hpc_mutex(2);
	}
	return (safeclose(*setup->socket), free_fake_env(setup->envp), free(setup), NULL);
}
