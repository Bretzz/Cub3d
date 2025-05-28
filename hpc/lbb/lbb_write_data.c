/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_write_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:16:46 by totommi           #+#    #+#             */
/*   Updated: 2025/05/21 00:59:30 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

int		lbb_add_player(const char *msg);
int		lbb_update_player(const char *msg);
void	*lbb_kill_player(const char *msg);
void	*lbb_move_player(int src, int dest);
void	lbb_push_up(void);

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
ALSO returns said pointer if NULL is passed. */
void	*lbb_kill_player(const char *msg)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	int				index;
	static void		*small;

	if (msg == NULL)
		return (small);
	if (*msg == 0x7f)
		small = (void *)msg;
	index = lbb_get_index(msg);
	if (index < 0)
		return (NULL);
	ft_printf("killing %s\n", lobby[index].name);
	if (lobby[index].online > small)
		free(lobby[index].online);
	ft_memset(&lobby[index], 0, sizeof(t_player));
	return (NULL);
}

/* moves the player at the index 'src' to the index 'dest'.
After that bzeros the player 'src'.
RETURNS: a ptr to the new player 'src' index (dest), NULL if player is null. */
void	*lbb_move_player(int src, int dest)
{
	t_player *const	lobby = lbb_get_ptr(NULL);

	if (lobby == NULL)
		return (NULL);
	if (src < 0 || src >= MAXPLAYERS)
		return (NULL);
	if (dest < 0 || dest >= MAXPLAYERS)
		return (NULL);
	if (dest == src)
		return (NULL);
	ft_memmove(&lobby[dest], &lobby[src], sizeof(t_player));
	ft_memset(&lobby[src], 0, sizeof(t_player));
	return (&lobby[dest]);
}

/* compacts to the top all the players left.
ex:
[0]: host
[1]:
[2]: player2
[3]: 
[4]: player4
->
[0]: host
[1]: player2
[2]: player4
[3]:
[4]: */
void	lbb_push_up(void)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	int				i[2];
	int				slot;

	if (lobby == NULL)
		return ;
	i[0] = 0;
	while (i[0] < MAXPLAYERS)
	{
		slot = lbb_next_free_slot();
		if (slot < 0)
			break ;
		i[1] = slot + 1;
		while (i[1] < MAXPLAYERS)
		{
			if (lbb_is_alive(lobby[i[1]]))
			{
				lbb_move_player(i[1], slot);
				break ;
			}
			i[1]++;
		}
		i[0]++;
	}
}
