/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2d_mini_lobby.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:11:19 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 17:13:33 by topiana-         ###   ########.fr       */
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

static void	put2d_mini_nametag(t_mlx *mlx, int index,
	t_player player, unsigned int color)
{
	const int	side = mlx->map.mini_side;
	const int	start_x = (mlx->map.stats[0]) * side + MINIMAP_OFFSET;
	const int	start_y = MINIMAP_OFFSET + ((index * 3.5f) * side);
	const int	origin[2] = {start_x + side / 2, start_y + side / 2.5f};

	put_square(mlx->img, side * 2, (int *)origin, color);
	yft_string_put(mlx->img[0].img_ptr,
		start_x + side * 2.5f,
		start_y - side, player.name);
}

/* puts the player's pos on the minimap */
int	put2d_mini_lobby(t_mlx *mlx, size_t side)
{
	int				i;
	unsigned int	color;

	i = 0;
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(mlx->fake_lobby[i]))
		{
			color = 0;
			if (mlx->fake_lobby[i].extra != NULL)
				color = ((t_sprite *)mlx->fake_lobby[i].extra)->chroma;
			if (mlx->online)
				put2d_mini_nametag(mlx, i, mlx->fake_lobby[i], color);
			if ((i == mlx->fake_index || mlx->fake_lobby[i].data[2] != 0)
				&& mlx->fake_lobby[i].extra != NULL)
				put2d_mini_player(mlx, (float *)mlx->fake_lobby[i].pos,
					side, color);
		}
		i++;
	}
	return (0);
}
