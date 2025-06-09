/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2d_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:37:13 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 22:32:18 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	put2d_minimap(t_mlx *mlx, size_t side);

static int	put_left_right_mini_border(t_mlx *mlx, int side)
{
	const float	incr = ((float)mlx->map.stats[1] / 2) / side;
	float		point;
	int			pixel[4];

	pixel[0] = MINIMAP_OFFSET;
	pixel[2] = (mlx->map.stats[0] * side) + MINIMAP_OFFSET;
	point = 0;
	while (point < mlx->map.stats[1] * side)
	{
		pixel[1] = point + incr + MINIMAP_OFFSET - 1;
		pixel[3] = point + incr + MINIMAP_OFFSET - 1;
		put_square(mlx, side / 2, pixel, 0x000000);
		put_square(mlx, side / 2, &pixel[2], 0x000000);
		point += incr;
	}
	// ft_printf("left_righ out\n");
	return (0);
}

static int	put_top_bottom_mini_border(t_mlx *mlx, int side)
{
	const float	incr = ((float)mlx->map.stats[0] / 2) / side;
	float		point;
	int			pixel[4];

	pixel[1] = MINIMAP_OFFSET;
	pixel[3] = (mlx->map.stats[1] * side) + MINIMAP_OFFSET;
	point = 0;
	while (point < mlx->map.stats[0] * side)
	{
		// printf("%d -> %f -> %d\n", MINIMAP_OFFSET, point, mlx->map.stats[0] * side);
		pixel[0] = point + incr + MINIMAP_OFFSET - 1;
		pixel[2] = point + incr + MINIMAP_OFFSET - 1;
		put_square(mlx, side / 2, pixel, 0x000000);
		put_square(mlx, side / 2, &pixel[2], 0x000000);
		point += incr;
	}
	// ft_printf("top_bot out\n");
	return (0);
}

/* puts the map (mlx->map.mtx) on the screen.
if mlx->map.mtx is NULL segfaults.
color is the color of the walls,
side is the length of the single square unit in pixel. */
static int	put2d_mini_map(t_mlx *mlx, int side, unsigned int color)
{
	int	pixel[2];

	pixel[1] = 0;
	while (mlx->map.mtx[pixel[1]] != NULL)
	{
		pixel[0] = 0;
		while (mlx->map.mtx[pixel[1]][pixel[0]] != '\0')
		{
			if (mlx->map.mtx[pixel[1]][pixel[0]] == '1')
			{
				operation_array(pixel, 2, side, '*');
				operation_array(pixel, 2, MINIMAP_OFFSET, '+');
				put_square(mlx, side, pixel, color);
				operation_array(pixel, 2, MINIMAP_OFFSET, '-');
				operation_array(pixel, 2, side, '/');
			}
			pixel[0]++;
		}
		pixel[1]++;
	}
	// ft_printf("minimap out\n");
	return (0);
}

/* side is the length of the single square unit in pixel */
static int	put2d_mini_player(t_mlx *mlx, float *pos,
				int side, unsigned int color)
{
	const int	scale_pos[2] = {(pos[0] - 0.25f) * side + MINIMAP_OFFSET,
		(pos[1] - 0.25f) * side + MINIMAP_OFFSET};

	put_square(mlx, side / 2, (int *)scale_pos, color);
	return (0);
}

/* puts the minimap and the single player
location/direction */
/* LOBBY MUTEX */
int	put2d_minimap(t_mlx *mlx, size_t side)
{
	int	i;

	put2d_mini_map(mlx, side, 0x0000ff);
	put_top_bottom_mini_border(mlx, side);
	put_left_right_mini_border(mlx, side);
	i = 0;
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(mlx->fake_lobby[i])
			&& mlx->fake_lobby[i].extra != NULL)
		{
			put2d_mini_player(mlx, (float *)mlx->fake_lobby[i].pos,
				side, ((t_sprite *)mlx->fake_lobby[i].extra)->chroma);
		}
		i++;
	}
	return (0);
}
