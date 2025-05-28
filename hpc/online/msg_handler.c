/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:31:36 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 22:57:02 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "online.h"
#include <errno.h>

int	parse_msg_string(const char *msg);
int	one_player_action(const char *msg, t_player *lobby, void *online);
int	cycle_player_msgs(char *msg, t_player *print_lobby);

/* checks weather msg is a valid string and checks the
action to be performed.
RETURNS:
	-1: invalid msg,
	0: action not specified,
	1: update action,
	2: kill action,
	3: host action. */
int	parse_msg_string(const char *msg)
{
	int	action;

	if (!msg_ip_length(msg) || !msg_name_length(msg))
		return (-1);
	action = str_skip(msg, 4, ':');
	if (msg[action] == '\0')
		return (0);
	if (!ft_strncmp("new", &msg[action], 4))
		return (1);
	if (!ft_strncmp("update", &msg[action], 7))
		return (2);
	if (!ft_strncmp("kill", &msg[action], 5))
		return (3);
	if (!ft_strncmp("host", &msg[action], 5))
		return (4);
	return (0);
}

int	one_player_action(const char *msg, t_player *lobby, void *online)
{
	const int	action = parse_msg_string(msg);

	ft_printf(LOG"action value %d%s\n", action, RESET);
	if (action <= 0)
		errno = 256;
	else if (lobby == NULL)
	{
		errno = 257;
		return (0);
	}
	else if (action == 1)
		new_player(msg, lobby, online);
	else if (action == 2)
		update_player(msg, lobby, online);
	else if (action == 3)
		lbb_kill_player(msg);
	else if (action == 4)
		host_player(msg, lobby);
	else
		errno = 1;
	return (action);	//may be necessary to set manually errno to 0 before
}

int	cycle_player_msgs(char *msg, t_player *lobby)
{
	unsigned int	i;
	unsigned int	last;

	last = 0;
	i = 0;
	while (msg[i] != '\0')
	{
		if (msg[i] == '\n')
		{
			msg[i] = '\0';
			if (one_player_action(&msg[last], lobby, NULL) <= 0)
				return (0);
			last = i + 1;
		}
		i++;
	}
	if (one_player_action(&msg[last], lobby, NULL) <= 0)
		return (0);
	return (1);
}
	