/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:56:46 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/30 11:39:43 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* put a square in the window, (x, y) are the coordinates
of the top left corner. */
int	put_square(t_mlx *mlx, size_t side, int *origin, unsigned int color)
{
	int	pixel[2];

	pixel[0] = origin[0];
	while ((size_t)pixel[0] < origin[0] + side)
	{
		pixel[1] = origin[1];
		while ((size_t)pixel[1] < origin[1] + side)
		{
			my_pixel_put(mlx, pixel[0], pixel[1], color);
			pixel[1]++;
		}
		pixel[0]++;
	}
	return (0);
}

/* puts the map (mlx->map.mtx) on the screen.
if mlx->map.mtx is NULL segfaults.
color is the color of the walls,
side is the length of the single square unit in pixel. */
int	put2d_map(t_mlx *mlx, int side, unsigned int color)
{
	unsigned int	pixel[2];

	pixel[1] = 0;
	while (mlx->map.mtx[pixel[1]] != NULL)
	{
		pixel[0] = 0;
		while (mlx->map.mtx[pixel[1]][pixel[0]] != '\0')
		{
			if (mlx->map.mtx[pixel[1]][pixel[0]] == '1')
			{
				pixel[0] *= side;
				pixel[1] *= side;
				put_square(mlx, side, (int *)pixel, color);
				pixel[0] /= side;
				pixel[1] /= side;
			}
			pixel[0]++;
		}
		pixel[1]++;
	}
	return (0);
}

/* side is the length of the single square unit in pixel */
int	put2d_player(t_mlx *mlx, float *pos, int side, unsigned int color)
{
	const int	scale_pos[2] = {pos[0] * side,
		pos[1] * side};

	put_square(mlx, side / 2, (int *)scale_pos, color);
	return (0);
}

/* side is the length of the single square unit in pixel */
int	put2d_ray(void *my_struct, int side, float null2, unsigned int color)
{
	t_mlx *const	mlx = (t_mlx *)my_struct;
	int				ray[2];
	int				pos[2];

	(void)null2;
	if (mlx->ray.hit[0] != 0 || mlx->ray.hit[1] != 0)
	{
		ray[0] = mlx->ray.hit[0] * side;
		ray[1] = mlx->ray.hit[1] * side;
		pos[0] = mlx->player.pos[0] * side;
		pos[1] = mlx->player.pos[1] * side;
		put_line(mlx, pos, ray, color);
	}
	return (0);
}
