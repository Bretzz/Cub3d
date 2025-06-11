/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:33:29 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/10 15:50:18 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "actions.h"

void	fire_player(const char *msg, t_player *lobby);
void	hit_player(const char *msg, t_player *lobby);

/* LOBBY MUTEX */
/* Sets the 'shooting' variable to 1 */
void	fire_player(const char *msg, t_player *lobby)
{
	int	slot;

	lbb_mutex(1);
	slot = lbb_get_index(msg);
	if (slot < 0 && lbb_mutex(2))
		return ;
	lobby[slot].data[0] = 4;
	lbb_mutex(2);
}

/* LOBBY MUTEX */
/* decrease the player's hp by one */
void	hit_player(const char *msg, t_player *lobby)
{
	int	slot;

	lbb_mutex(1);
	slot = lbb_get_index(msg);
	if (slot < 0 && lbb_mutex(2))
		return ;
	lobby[slot].data[1]--;
	lbb_mutex(2);
}
