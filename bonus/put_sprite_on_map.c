/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite_on_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:59:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/29 23:48:38 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

#include <stdio.h>

int	put_sprite_on_map(t_mlx *mlx, float *pos, t_sprite sprite, int chroma);

/* adds the sprite to the mlx->img
starting from x_screen and y_screen and scaled
by a factor (scale).
NOTE: future implementation: passing the sprite pointer and the
dimensions of the sprite. */
static int	put_sprite(t_mlx *mlx, t_plot plot, t_sprite sprite, int chroma)
{
	const unsigned int	c_map[6] = { 0x714333, 0xff00fa, 0xff0000, 0x00ff00, 0x0000ff, 0xa0b0c0};
	const int			new_width = (sprite.width * sprite.scale);
	const int			new_heigth = (sprite.heigth * sprite.scale);
	int					win_x_y[2];
	int					src_x_y[2];
	unsigned int		color;

	win_x_y[1] = 0;
	while (win_x_y[1] < new_heigth && win_x_y[1] + (plot.y_screen - (new_heigth / 2)) < mlx->win_y)
	{
		win_x_y[0] = 0;
		while (win_x_y[0] < new_width && win_x_y[0] + (plot.x_screen - (new_width / 2)) < mlx->win_x)
		{
			src_x_y[0] = win_x_y[0] * sprite.width / new_width;
			src_x_y[1] = win_x_y[1] * sprite.heigth / new_heigth;
			color = get_pixel_color(sprite.image, src_x_y[0], src_x_y[1]);
			if ((unsigned int)color < 100000000)	// don't plot black
			{
				if (color == 0x714333)
					color = c_map[chroma % 6];
				my_pixel_put(mlx,
					win_x_y[0] + (plot.x_screen - (new_width / 2)),
					win_x_y[1] + (plot.y_screen - (new_heigth / 2)),
					color);
			}
			win_x_y[0]++;
		}
		win_x_y[1]++;
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

/* difference in direction after making them comparable.
(used for comparing dirs and atan2() returns) */
float	dir_diff(float dir1, float dir2)
{
	return (monoscale_dir(dir1) - monoscale_dir(dir2));
}


/* (x,y) position of the sprite in the map,
'len' is the distance from the sprite
'dir' is the angle (degrees) we are looking the sprite from
if 'hp' is bigger than 0, the health bar will be shown */
int	put_sprite_on_map(t_mlx *mlx, float *pos, t_sprite sprite, int chroma)
{
	const int	mid_line = cos(mlx->player.dir[1] * M_PI / 180) * (2 * mlx->win_y) + (mlx->win_y / 2);
	const float	*my_pos = mlx->player.pos;
	const float	sprite_dir = atan2((my_pos[1] - pos[1]), (my_pos[0] - pos[0])) * 180 / M_PI;
	float		my_dist;
	int			x_screen;

	ft_memset(&mlx->player.sprite_data, 0, sizeof(t_plot));
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
	my_dist = sqrt(pow(pos[0] - my_pos[0], 2) + pow(pos[1] - my_pos[1], 2));
	// ft_printf("check\n");
	if (mlx->ray.len > 0 && mlx->ray.len < my_dist)
	{
		// ft_printf("OBSTACLE OUT\n");
		return (1);
	}
	// putting sprite

	int floor = (mlx->win_x) / my_dist;
	floor -= floor / ((/* 1 /  */mlx->player.pos[2] / (pos[2] + 1)) + 1);
	x_screen = (mlx->win_x / 2) + dir_diff(sprite_dir, mlx->player.dir[0]) * (mlx->win_x / mlx->player.fov[0]);
	// ft_printf("before\n");
	// ft_printf("spriting (%d, %d)\n", x_screen, mid_line + floor);
	sprite.scale = ((mlx->win_x / 2) / sprite.heigth) / my_dist;
	// printf("got scale %f\n", sprite.scale);
	// ft_memset(&mlx->player.sprite_data, 0, sizeof(t_plot));
	mlx->player.sprite_data.width = sprite.width;
	mlx->player.sprite_data.heigth = sprite.heigth;
	mlx->player.sprite_data.scale = sprite.scale;
	mlx->player.sprite_data.x_screen = x_screen;
	mlx->player.sprite_data.y_screen = mid_line + floor;
	mlx->player.sprite_data.dist = my_dist;
	// ft_printf("after\n");
	put_sprite(mlx, mlx->player.sprite_data, sprite, chroma);
	return (0);
}
