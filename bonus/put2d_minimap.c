/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2d_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:37:13 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 17:16:08 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	put2d_minimap(t_mlx *mlx, size_t side);

static int	put_left_right_mini_border(t_mlx *mlx, int side)
{
	const float	incr = ((float)mlx->map.stats[1] / 2) / side;
	const float	half_side = side / 2;
	float		point;
	int			pixel[4];

	pixel[0] = 0;
	pixel[2] = (mlx->map.stats[0] * side) - half_side;
	point = 0;
	while (point < mlx->map.stats[1] * side)
	{
		pixel[1] = point + incr - 1;
		pixel[3] = point + incr - 1;
		put_square(&mlx->img[1], half_side, pixel, 0x000000);
		put_square(&mlx->img[1], half_side, &pixel[2], 0x000000);
		point += incr;
	}
	return (0);
}

static int	put_top_bottom_mini_border(t_mlx *mlx, int side)
{
	const float	incr = ((float)mlx->map.stats[0] / 2) / side;
	const float	half_side = side / 2;
	float		point;
	int			pixel[4];

	pixel[1] = 0;
	pixel[3] = (mlx->map.stats[1] * side) - half_side;
	point = 0;
	while (point < mlx->map.stats[0] * side)
	{
		pixel[0] = point + incr - 1;
		pixel[2] = point + incr - 1;
		put_square(&mlx->img[1], half_side, pixel, 0x000000);
		put_square(&mlx->img[1], half_side, &pixel[2], 0x000000);
		point += incr;
	}
	return (0);
}

/* if mlx->map.mtx is NULL segfaults.
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
				put_square(&mlx->img[1], side, pixel, color);
				operation_array(pixel, 2, side, '/');
			}
			else
			{
				operation_array(pixel, 2, side, '*');
				put_square(&mlx->img[1], side, pixel, 0xffffff);
				operation_array(pixel, 2, side, '/');
			}
			pixel[0]++;
		}
		pixel[1]++;
	}
	return (0);
}

/* creates the mlx->map.mini_img image.
puts the minimap and the single player location/direction */
/* LOBBY MUTEX */
int	put2d_minimap(t_mlx *mlx, size_t side)
{
	put2d_mini_map(mlx, side, 0x0000ff);
	put_top_bottom_mini_border(mlx, side);
	put_left_right_mini_border(mlx, side);
	return (0);
}
