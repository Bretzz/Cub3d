/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:03:47 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/31 17:05:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"

void	new_player(const char *msg, t_player *lobby, void *online);
void	update_player(const char *msg, t_player *lobby, void *online);
void	kill_player(const char *msg, t_player *lobby);
void	host_player(const char *msg, t_player *lobby);
void	fire_player(const char *msg, t_player *lobby);
void	hit_player(const char *msg, t_player *lobby);

/* LOBBY MUTEX */
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
	lobby[slot].hp = PLAYER_HP;
	lbb_mutex(2);
}

/* LOBBY MUTEX */
void	update_player(const char *msg, t_player *lobby, void *online)
{
	int	slot;

	lbb_mutex(1);
	slot = lbb_get_index(msg);
	if (slot < 0 && lbb_mutex(2))
		return ;
	// ft_printf("updating %d\n", slot);
	msg_get_pos(msg, lobby[slot].pos);
	msg_get_tar(msg, lobby[slot].tar);
	// msg_get_pos_tar(msg, lobby[slot].pos_tar);
	if (online != NULL)
		lobby[slot].online = online;
	lbb_mutex(2);
}

/* LOBBY MUTEX */
void	kill_player(const char *msg, t_player *lobby)
{
	int	slot;

	lbb_mutex(1);
	slot = lbb_get_index(msg);
	if (slot < 0 && lbb_mutex(2))
		return ;
	free(lobby[slot].extra);
	lbb_kill_player(msg);
	lbb_mutex(2);
}

/* LOBBY MUTEX */
void	host_player(const char *msg, t_player *lobby)
{
	int	slot;

	lbb_mutex(1);
	(void)lobby;
	slot = lbb_get_index(msg);
	if (slot < 0 && lbb_mutex(2))
		return ;
	free(lobby[HOST].online);	// could be done better
	lbb_move_player(slot, 0);
	// lbb_push_up();			// comment so that color don't change
	lbb_mutex(2);
}

/* LOBBY MUTEX */
void	fire_player(const char *msg, t_player *lobby)
{
	int	slot;

	lbb_mutex(1);
	slot = lbb_get_index(msg);
	if (slot < 0 && lbb_mutex(2))
		return ;
	lobby[slot].shoot = 1;
	lbb_mutex(2);
}

/* LOBBY MUTEX */
void	hit_player(const char *msg, t_player *lobby)
{
	int	slot;

	lbb_mutex(1);
	slot = lbb_get_index(msg);
	if (slot < 0 && lbb_mutex(2))
		return ;
	lobby[slot].hp--;
	lbb_mutex(2);
}
