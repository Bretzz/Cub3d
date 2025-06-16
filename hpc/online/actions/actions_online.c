/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_online.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:03:47 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/10 15:48:09 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "actions.h"

void	new_player(const char *msg, t_player *lobby, void *online);
void	update_player(const char *msg, t_player *lobby, void *online);
void	kill_player(const char *msg, t_player *lobby);
void	host_player(const char *msg, t_player *lobby);

/* LOBBY MUTEX */
/* adds the new player to the lobby or updates the 'online'
parameter */
void	new_player(const char *msg, t_player *lobby, void *online)
{
	int	slot;

	lbb_mutex(1);
	if (lbb_get_index(msg) >= 0)
	{
		if (online != NULL)
			lobby[lbb_get_index(msg)].online = online;
		lbb_mutex(2);
		return ;
	}
	slot = lbb_next_free_slot();
	if (slot < 0 && lbb_mutex(2))
		return ;
	msg_get_name(msg, lobby[slot].name);
	msg_get_ip(msg, lobby[slot].ip);
	msg_get_pos(msg, lobby[slot].pos);
	msg_get_tar(msg, lobby[slot].tar);
	if (online != NULL)
		lobby[slot].online = online;
	lobby[slot].data[1] = PLAYER_HP;
	lbb_mutex(2);
}

/* LOBBY MUTEX */
/* updates pos, tar and occasionally online */
void	update_player(const char *msg, t_player *lobby, void *online)
{
	int	slot;

	lbb_mutex(1);
	slot = lbb_get_index(msg);
	if (slot < 0 && lbb_mutex(2))
		return ;
	msg_get_pos(msg, lobby[slot].pos);
	msg_get_tar(msg, lobby[slot].tar);
	if (online != NULL)
		lobby[slot].online = online;
	lbb_mutex(2);
}

/* LOBBY MUTEX */
/* kills the player, freeing resources and bzeroing
all the struct */
void	kill_player(const char *msg, t_player *lobby)
{
	int	slot;

	lbb_mutex(1);
	(void)lobby;
	slot = lbb_get_index(msg);
	if (slot < 0 && lbb_mutex(2))
		return ;
	lbb_kill_player(msg);
	lbb_mutex(2);
}

/* LOBBY MUTEX */
/* moves the player at the top of the lobby.
old behaviour: lbb_push_up() after moving the host. */
void	host_player(const char *msg, t_player *lobby)
{
	int	slot;

	lbb_mutex(1);
	slot = lbb_get_index(msg);
	if (slot < 0 && lbb_mutex(2))
		return ;
	if (lobby[HOST].online >= lbb_kill_player(NULL))
		free(lobby[HOST].online);
	ft_memset(&lobby[HOST], 0, sizeof(t_player) - sizeof(void *));
	lbb_swap_player(slot, HOST);
	lbb_mutex(2);
}
