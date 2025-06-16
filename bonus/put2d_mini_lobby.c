/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2d_mini_lobby.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:11:19 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/11 17:11:40 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* side is the length of the single square unit in pixel */
static int	put2d_mini_player(t_mlx *mlx, float *pos,
				int side, unsigned int color)
{
	const int	scale_pos[2] = {(pos[0] - 0.25f) * side,
		(pos[1] - 0.25f) * side};

	put_square(&mlx->img[1], side / 1.25f, (int *)scale_pos, color);
	return (0);
}

/* puts the player's pos on the minimap */
int	put2d_mini_lobby(t_mlx *mlx, size_t side)
{
	int	i;

	i = 0;
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(mlx->fake_lobby[i])
			&& (i == mlx->fake_index || mlx->fake_lobby[i].data[2] != 0)
			&& mlx->fake_lobby[i].extra != NULL)
		{
			put2d_mini_player(mlx, (float *)mlx->fake_lobby[i].pos,
				side, ((t_sprite *)mlx->fake_lobby[i].extra)->chroma);
		}
		i++;
	}
	return (0);
}
