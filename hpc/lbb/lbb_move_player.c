/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_move_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 00:32:01 by totommi           #+#    #+#             */
/*   Updated: 2025/06/08 00:39:40 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"

void	*lbb_move_player(int src, int dest);
void	*lbb_swap_player(int src, int dest);
void	lbb_push_up(void);

/* moves the player at the index 'src' to the index 'dest'.
After that bzeros the player 'src' (not anymore).
! ! ! DEPRECATED ! ! ! (online and extra pointer losts)
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

/* like lbb_move_player but just swaps them */
void	*lbb_swap_player(int src, int dest)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	t_player		temp;

	if (lobby == NULL)
		return (NULL);
	if (src < 0 || src >= MAXPLAYERS)
		return (NULL);
	if (dest < 0 || dest >= MAXPLAYERS)
		return (NULL);
	if (dest == src)
		return (NULL);
	ft_memmove(&temp, &lobby[dest], sizeof(t_player));
	ft_memmove(&lobby[dest], &lobby[src], sizeof(t_player));
	ft_memmove(&lobby[src], &temp, sizeof(t_player));
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
