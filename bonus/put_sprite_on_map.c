/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite_on_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:59:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 21:55:57 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

#include <stdio.h>

int	put_sprite_on_map(t_mlx *mlx, float *pos, t_sprite sprite);

/* junky as hell, useful for difference in directions
that are normalize usually in (-180, 180] in other parts
of the code */
static float	monoscale_dir(float dir)
{
	if (dir <= -90)
		return (360 + dir);
	if (dir > 360)
		return (dir - 360);
	return (dir);
}

/* difference in direction after making them comparable.
(used for comparing dirs and atan2() returns) */
float	dir_diff(float dir1, float dir2)
{
	return (monoscale_dir(dir1) - monoscale_dir(dir2));
}

static void	set_sprite_data(t_mlx *mlx,
	float *pos, float my_dist, float sprite_dir)
{
	const int	mid_line = cos(mlx->player.dir[1] * MY_PI / 180)
		* (2 * MLX_WIN_Y) + (MLX_WIN_Y / 2);
	const int	x_screen = (MLX_WIN_X / 2) + dir_diff(sprite_dir,
			mlx->player.dir[0]) * (MLX_WIN_X / mlx->player.fov[0]);
	const int	floor = (MLX_WIN_X / my_dist) - ((MLX_WIN_X / my_dist)
			/ ((mlx->player.pos[2] / (pos[2] + 1)) + 1));

	mlx->pos_data[MAXPLAYERS].seen = 1;
	mlx->pos_data[MAXPLAYERS].x_screen = x_screen;
	mlx->pos_data[MAXPLAYERS].y_screen = mid_line + floor;
	mlx->pos_data[MAXPLAYERS].dist = my_dist;
	mlx->pos_data[MAXPLAYERS].dir = sprite_dir;
}

/* (x,y) position of the sprite in the map,
'len' is the distance from the sprite
'dir' is the angle (degrees) we are looking the sprite from
if 'hp' is bigger than 0, the health bar will be shown */
int	put_sprite_on_map(t_mlx *mlx, float *pos, t_sprite sprite)
{
	const float	*my_pos = mlx->player.pos;
	const float	sprite_dir = atan2((my_pos[1] - pos[1]),
			(my_pos[0] - pos[0])) * 180 / MY_PI;
	const float	my_dist = sqrt((pos[0] - my_pos[0]) * (pos[0] - my_pos[0])
			+ (pos[1] - my_pos[1]) * (pos[1] - my_pos[1]));

	ft_memset(&mlx->pos_data[MAXPLAYERS], 0, sizeof(t_plot));
	mlx->pos_data[MAXPLAYERS].dist = my_dist;
	mlx->pos_data[MAXPLAYERS].dir = sprite_dir;
	if (fabsf(dir_diff(sprite_dir, mlx->player.dir[0]))
		> mlx->player.fov[0] / 2)
		return (1);
	cast_ray(mlx, my_pos[0], my_pos[1], sprite_dir);
	if (mlx->ray.len > 0 && mlx->ray.len < my_dist)
		return (1);
	sprite.scale = ((MLX_WIN_X / 2) / sprite.heigth) / my_dist;
	ft_memmove(&mlx->pos_data, &sprite, 3 * sizeof(int));
	set_sprite_data(mlx, pos, my_dist, sprite_dir);
	put_sprite(mlx, mlx->pos_data[MAXPLAYERS], sprite);
	return (0);
}
