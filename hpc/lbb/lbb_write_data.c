/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_write_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:16:46 by totommi           #+#    #+#             */
/*   Updated: 2025/06/08 00:32:52 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"
#include "libft.h"
#include "msg.h"

int		lbb_add_player(const char *msg);
int		lbb_update_player(const char *msg);
void	*lbb_kill_player(const char *msg);

/* takes a msg-string as parameter.
adds the data of the player found (if there's any empty slot in the lobby).
RETURNS: 1 if data was written successfully,
0 if msg is NULL or lobby is full. */
int	lbb_add_player(const char *msg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	int				slot;

	if (!lobby || !msg)
		return (0);
	slot = lbb_next_free_slot();
	if (slot < 0)
		return (0);
	msg_get_name(msg, lobby[slot].name);
	msg_get_ip(msg, lobby[slot].ip);
	msg_get_pos(msg, lobby[slot].pos);
	msg_get_tar(msg, lobby[slot].tar);
	msg_get_pos_tar(msg, lobby[slot].pos_tar);
	return (1);
}

/* takes a msg-string as parameter.
updates the data of the player found.
RETURNS: 1 if data was written successfully, 0 if the player wasn't found */
int	lbb_update_player(const char *msg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	int				index;

	if (!lobby || !msg)
		return (0);
	index = lbb_get_index(msg);
	if (index < 0)
		return (0);
	msg_get_pos(msg, lobby[index].pos);
	msg_get_tar(msg, lobby[index].tar);
	msg_get_pos_tar(msg, lobby[index].pos_tar);
	return (1);
}

/* clears the struct's bytes.
You can pass a pointer to an escape (0x7f) char
to set the treshold of the smallest to free.
ALSO returns said pointer if NULL is passed.
NOTE: the 'extra' pointer isn't bzeroed.
needs to free(3) it manually. */
void	*lbb_kill_player(const char *msg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	int				index;
	static void		*small;

	if (msg == NULL)
		return (small);
	if (*msg == 0x7f)
	{
		small = (void *)msg;
		return (small);
	}
	index = lbb_get_index(msg);
	if (index < 0)
		return (NULL);
	if (lobby[index].online > small)
		free(lobby[index].online);
	ft_memset(&lobby[index], 0, sizeof(t_player) - sizeof(void *));
	return (NULL);
}
