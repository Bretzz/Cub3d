/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:59:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/22 10:50:38 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <stdio.h>

/* adds the sprite to the mlx->img
starting from x_screen and y_screen and scaled
by a factor (scale).
NOTE: future implementation: passing the sprite pointer and the
dimensions of the sprite. */
int	put_sprite(t_mlx *mlx, int x_screen, int y_screen, float scale)
{
	const int	new_width = (mlx->player.sprite_x * scale);
	const int	new_heigth = (mlx->player.sprite_y * scale);
	int			y;
	int			x;

	y = 0;
	while (y < new_heigth && y + (y_screen - (new_heigth / 2)) < mlx->win_y)
	{
		x = 0;
		while (x < new_width && x + (x_screen - (new_width / 2)) < mlx->win_x)
		{
			int src_x = x * mlx->player.sprite_x / new_width;
			int src_y = y * mlx->player.sprite_y / new_heigth;
			my_pixel_put(mlx,
				x + (x_screen - (new_width / 2)),
				y + (y_screen - (new_heigth / 2)),
				get_pixel_color(mlx->player.sprite, src_x, src_y));
			x++;
		}
		y++;
	}
	return (0);
}

/* (x,y) position of the sprite in the map,
'len' is the distance from the sprite
'dir' is the angle (degrees) we are looking the sprite from */
int	put_sprite_on_map(t_mlx *mlx, float x, float y)
{
	const int	mid_line = cos(mlx->player.dir[1] * M_PI / 180) * (2 * mlx->win_y) + (mlx->win_y / 2);
	const float	*my_pos = mlx->player.pos;
	const float	sprite_dir = atan2((my_pos[1] - y), (my_pos[0] - x)) * 180 / M_PI;
	float		my_dist;
	int			x_screen;

	// visibility check
	if (sprite_dir < mlx->player.dir[0] - (mlx->player.fov[0] / 2)
		|| sprite_dir > mlx->player.dir[0] + (mlx->player.fov[0] / 2))
		return (1);
	// obstacle check
	cast_ray(mlx, my_pos[0], my_pos[1], sprite_dir);
	my_dist = sqrt(pow(x - my_pos[0], 2) + pow(y - my_pos[1], 2));
	if (mlx->ray.len > 0 && mlx->ray.len < my_dist)
		return (1);
	// putting sprite
	x_screen = (mlx->win_x / 2) + (sprite_dir - mlx->player.dir[0]) * (mlx->win_x / mlx->player.fov[0]);
	put_sprite(mlx, x_screen, mid_line, ((mlx->win_x / 2) / mlx->player.sprite_y) / my_dist);
	return (0);
}
