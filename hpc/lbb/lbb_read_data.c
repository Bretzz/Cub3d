/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_read_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:54:44 by totommi           #+#    #+#             */
/*   Updated: 2025/05/07 12:20:31 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

int		lbb_get_index(const char *msg);
int		lbb_next_free_slot(void);
int		lbb_is_alive(t_player player);
size_t	lbb_player_count(void);

/* Compares the player passed as parameter with a fully
zeroed player, if they match, the player passed is dead.
RETURNS: 0 if the player is dead, 1 if it isn't. */
int	lbb_is_alive(t_player player)
{
	t_player	dead_player;

	ft_memset(&dead_player, 0, sizeof(t_player));
	if (!ft_memcmp(&player, &dead_player, (sizeof(t_player) - sizeof(void *))))
		return (0);
	return (1);
}

/* Counts how many alive players are in the lobby.
(checks with the lbb_is_alive() function).
RETURNS: the number of players alive, 0 if the lobby pointer
isn't initialized or there are 0 players alive. */
size_t	lbb_player_count(void)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	size_t			count;
	int				i;

	if (lobby == NULL)
		return (0);
	count = 0;
	i = 0;
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(lobby[i]))
			count++;
		i++;
	}
	return (count);
}

/* Takes a msg-string, as parameter.
RETURNS: the index of the player matching name:ip, -1 if not found.
TODO: also just pass name/ip as parameter. */
int	lbb_get_index(const char *msg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	char			msg_name[43];
	char			msg_ip[16];
	int				i;

	if (!lobby || !msg)
		return (-1);
	msg_get_name(msg, msg_name);
	msg_get_ip(msg, msg_ip);
	i = 0;
	while (i < MAXPLAYERS)
	{
		if (!ft_strcmp(msg_name, lobby[i].name)
			&& !ft_strcmp(msg_ip, lobby[i].ip))
			return (i);
		i++;
	}
	return (-1);
}

/* RETURNS: the next empty slot of the lobby, -1 if lobby is full.*/
int	lbb_next_free_slot(void)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	int				slot;

	if (!lobby)
		return (-1);
	slot = 0;
	while (slot < MAXPLAYERS)
	{
		if (!lbb_is_alive(lobby[slot]))
			return (slot);
		slot++;
	}
	return (-1);
}
