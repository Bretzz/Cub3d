/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite_on_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:59:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 02:06:25 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

#include <stdio.h>

int		put_sprite_on_map(t_mlx *mlx, float x, float y, t_sprite sprite);

/* adds the sprite to the mlx->img
starting from x_screen and y_screen and scaled
by a factor (scale).
NOTE: future implementation: passing the sprite pointer and the
dimensions of the sprite. */
static int	put_sprite(t_mlx *mlx, int x_screen, int y_screen, t_sprite sprite)
{
	const int	new_width = (sprite.width * sprite.scale);
	const int	new_heigth = (sprite.heigth * sprite.scale);
	int			y;
	int			x;

	y = 0;
	while (y < new_heigth && y + (y_screen - (new_heigth / 2)) < mlx->win_y)
	{
		x = 0;
		while (x < new_width && x + (x_screen - (new_width / 2)) < mlx->win_x)
		{
			int src_x = x * sprite.width / new_width;
			int src_y = y * sprite.heigth / new_heigth;
			my_pixel_put(mlx,
				x + (x_screen - (new_width / 2)),
				y + (y_screen - (new_heigth / 2)),
				get_pixel_color(sprite.image, src_x, src_y));
			x++;
		}
		y++;
	}
	return (0);
}
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

/* difference in direction after making them comparable. */
static float	dir_diff(float dir1, float dir2)
{
	return (monoscale_dir(dir1) - monoscale_dir(dir2));
}


/* (x,y) position of the sprite in the map,
'len' is the distance from the sprite
'dir' is the angle (degrees) we are looking the sprite from */
int	put_sprite_on_map(t_mlx *mlx, float x, float y, t_sprite sprite)
{
	const int	mid_line = cos(mlx->player.dir[1] * M_PI / 180) * (2 * mlx->win_y) + (mlx->win_y / 2);
	const float	*my_pos = mlx->player.pos;
	const float	sprite_dir = atan2((my_pos[1] - y), (my_pos[0] - x)) * 180 / M_PI;
	float		my_dist;
	int			x_screen;

	// visibility check
	if (fabsf(dir_diff(sprite_dir, mlx->player.dir[0])) > mlx->player.fov[0] / 2)
	{
		// printf("DIRECTION OUT: %f\n not in %f\n", sprite_dir, mlx->player.dir[0]);
		return (1);
	}
	// obstacle check
	// ft_printf("sprite in\n");
	cast_ray(mlx, my_pos[0], my_pos[1], sprite_dir);
	// ft_printf("sprite out\n");
	my_dist = sqrt(pow(x - my_pos[0], 2) + pow(y - my_pos[1], 2));
	// ft_printf("check\n");
	if (mlx->ray.len > 0 && mlx->ray.len < my_dist)
	{
		// ft_printf("OBSTACLE OUT\n");
		return (1);
	}
	// putting sprite

	int floor = (mlx->win_x) / my_dist;
	floor -= floor / (mlx->player.pos[2] + 1);
	x_screen = (mlx->win_x / 2) + dir_diff(sprite_dir, mlx->player.dir[0]) * (mlx->win_x / mlx->player.fov[0]);
	// ft_printf("before\n");
	// ft_printf("spriting (%d, %d)\n", x_screen, mid_line + floor);
	sprite.scale = ((mlx->win_x / 2) / sprite.heigth) / my_dist;
	// printf("got scale %f\n", sprite.scale);
	put_sprite(mlx, x_screen, mid_line + floor, sprite);
	// ft_printf("after\n");
	return (0);
}
