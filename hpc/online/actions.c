/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:03:47 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 23:00:29 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"

void	new_player(const char *msg, t_player *lobby, void *online);
void	update_player(const char *msg, t_player *lobby, void *online);
// void	kill_player(const char *msg, t_player *lobby);
void	host_player(const char *msg, t_player *lobby);
void	shoot_player(const char *msg, t_player *lobby);

void	new_player(const char *msg, t_player *lobby, void *online)
{
	int	slot;

	ft_printf("adding new player?\n");
	if (lbb_get_index(msg) >= 0)
	{
		if (online != NULL)
			lobby[lbb_get_index(msg)].online = online;
		return ;
	}
	ft_printf("....\n");
	slot = lbb_next_free_slot();
	if (slot < 0)
		return ;
	ft_printf("adding new player!\n");
	msg_get_name(msg, lobby[slot].name);
	msg_get_ip(msg, lobby[slot].ip);
	msg_get_pos(msg, lobby[slot].pos);
	msg_get_tar(msg, lobby[slot].tar);
	if (online != NULL)
		lobby[slot].online = online;
}

void	update_player(const char *msg, t_player *lobby, void *online)
{
	int	slot;

	slot = lbb_get_index(msg);
	if (slot < 0)
		return ;
	// ft_printf("updating %d\n", slot);
	msg_get_pos(msg, lobby[slot].pos);
	msg_get_tar(msg, lobby[slot].tar);
	// msg_get_pos_tar(msg, lobby[slot].pos_tar);
	if (online != NULL)
		lobby[slot].online = online;
}

void	kill_player(const char *msg, t_player *lobby)
{
	int	slot;

	slot = lbb_get_index(msg);
	if (slot < 0)
		return ;
	ft_memset(&lobby[slot], 0, sizeof(t_player));
}

void	host_player(const char *msg, t_player *lobby)
{
	int	slot;

	(void)lobby;
	slot = lbb_get_index(msg);
	if (slot < 0)
		return ;
	free(lobby[HOST].online);	// could be done better
	lbb_move_player(slot, 0);
	lbb_push_up();
}

void	shoot_player(const char *msg, t_player *lobby)
{
	int	slot;

	slot = lbb_get_index(msg);
	if (slot < 0)
		return ;
	msg_get_pos(msg, lobby[slot].pos);
	msg_get_tar(msg, lobby[slot].tar);
	lobby[slot].shoot = 1;
}
