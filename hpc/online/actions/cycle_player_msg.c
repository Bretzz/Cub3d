/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_player_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:31:36 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/17 15:59:57 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "online.h"
#include "actions.h"
#include <errno.h>

int	parse_msg_string(const char *msg);
int	one_player_action(const char *msg, t_player *lobby, void *online);
int	cycle_player_msgs(char *msg, t_player *print_lobby);

/* checks weather msg is a valid string and checks the
action to be performed.
RETURNS:
	-1: invalid msg,
	0: action not specified,
	1: new action
	2: update action,
	3: kill action,
	4: host action,
	5: fire action,
	6: hit action. */
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
	if (!ft_strncmp("fire", &msg[action], 5))
		return (5);
	if (!ft_strncmp("hit", &msg[action], 4))
		return (6);
	if (!ft_strncmp("shutdown", &msg[action], 9))
		return (7);
	if (!ft_strncmp("ack", &msg[action], 4))
		return (8);
	return (0);
}

int	one_player_action(const char *msg, t_player *lobby, void *online)
{
	const int	action = parse_msg_string(msg);

	if (action <= 0)
		errno = 256;
	else if (lobby == NULL)
		errno = 257;
	else if (action == 1)
		new_player(msg, lobby, online);
	else if (action == 2)
		update_player(msg, lobby, online);
	else if (action == 3)
		kill_player(msg, lobby);
	else if (action == 4)
		host_player(msg, lobby);
	else if (action == 5)
		fire_player(msg, lobby);
	else if (action == 6)
		hit_player(msg, lobby);
	else if (action == 8)
		ack_data_from_msg(msg);
	else
		errno = 1;
	if (errno != 0)
		return (-1);
	return (action);
}

/* executes each action received
NOTE: no mutexes must be locked going in here */
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
