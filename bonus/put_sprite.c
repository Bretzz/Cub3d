/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:59:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 14:47:51 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <stdio.h>

unsigned int	get_pixel(void *sprite, int x, int y)
{
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	const void	*addr = mlx_get_data_addr(sprite, &bits_per_pixel, &line_length, &endian);
	const char	*dst = addr + (y * line_length + x * (bits_per_pixel / sizeof(int *)));
	return (*(unsigned int *)dst);
}

int	put_sprite(t_mlx *mlx, int x_screen, int y_screen, float scale)
{
	// ft_printf("putting sprite\n");
	int	new_width = (mlx->player.sprite_x * scale);
	int new_heigth =(mlx->player.sprite_y * scale);
	for (int y = 0; y < new_heigth; y++) {
		for (int x = 0; x < new_width; x++) {
			int src_x = x * mlx->player.sprite_x / new_width;
			int src_y = y * mlx->player.sprite_y / new_heigth;
			int color = get_pixel(mlx->player.sprite, src_x, src_y);
			my_pixel_put(mlx, x + (x_screen - (new_width / 2)), y + (y_screen - (new_heigth / 2)), color);
		}
	}
	// mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player.sprite, x, y);
	return (0);
}

/* (x,y) position of the sprite in the map,
'len' is the distance from the sprite
'dir' is the angle (degrees) we are looking the sprite from */
int	put_sprite_on_map(t_mlx *mlx, float x, float y, unsigned int color)
{
	const float	*my_pos = mlx->player.pos;
	const float	my_dist = sqrt(pow(x - my_pos[0], 2) + pow(y - my_pos[1], 2));
	const float sprite_dir = atan2((my_pos[1] - y), (my_pos[0] - x)) * 180 / M_PI;
	const float	ray	= cast_ray(mlx, my_pos[0], my_pos[1], sprite_dir);
	const int	mid_line = cos(mlx->player.dir[1] * M_PI / 180) * (2 * mlx->win_y) + (mlx->win_y / 2);

	// visibility check
	if (sprite_dir < mlx->player.dir[0] - (mlx->player.fov[0] / 2)
		|| sprite_dir > mlx->player.dir[0] + (mlx->player.fov[0] / 2))
		return (1);
	// ft_printf("sprint inside the fov\n");
	if (ray > 0 && ray < my_dist)
		return (1);
	// /* ft_ */printf("SEEING SPRITE: dir %f\n", sprite_dir);
	int x_screen = (mlx->win_x / 2) + (sprite_dir - mlx->player.dir[0]) * (mlx->win_x / mlx->player.fov[0]);
	// /* ft_ */printf("sprite on x_screen %d, diff dir %f\n", x_screen, (sprite_dir - mlx->player.dir[0]));
	// put_square(mlx, 10, x_screen, mlx->win_y / 2, color);
	put_sprite(mlx, x_screen, mid_line, (mlx->win_y / (25/* mlx->player.sprite_y / 4 */)) / my_dist);
	(void)color;
	return (0);
}

// int	put_player(t_mlx *mlx, int *my_pos, int *his_pos, unsigned int color)
// {
// 	(void)mlx; (void)my_pos; (void)his_pos; (void)color;
// 	const float delta_angle = (mlx->player.fov[0] * M_PI / 180) / mlx->win_x;	// 0 = left, pi/2 = up
// 	const float angle = normalize_angle(atan2((my_pos[1] - his_pos[1]), (my_pos[0] - his_pos[0])));
// 	const float	my_dist = sqrt(pow(his_pos[0] - my_pos[0], 2) + pow(his_pos[1] - my_pos[1], 2));
// 	const float	dir = mlx->player.dir[0] * M_PI / 180;
// 	// mlx->player.fov[1] = 1;
// 	const float	ray	= cast_ray(mlx, my_pos, angle);
// 	// mlx->player.fov[1] = 0;

// 	(void)delta_angle;
// 	// ft_printf("player dist = %d\n", my_dist);
// 	// visibility check
// 	if (angle < dir - mlx->player.fov[0] * M_PI / 90
// 		|| angle > dir + mlx->player.fov[0] * M_PI / 90)
// 		return (1);
// 	if (ray > 0 && ray < my_dist)
// 		return (1);
// 	// visibility check
// 	// put_square(mlx, mlx->win_x / 2, mlx->win_y / 2, 0, 10, 0xed80e9);
	
// 	// mlx->win_x = player.fov
// 	int centre = mlx->win_x / 2 + (angle - dir) / delta_angle;
// 	put_centre_line(mlx, centre - 2, my_dist, color);
// 	put_centre_line(mlx, centre - 1, my_dist, color);
// 	put_centre_line(mlx, centre, my_dist, color);
// 	put_centre_line(mlx, centre + 1, my_dist, color);
// 	put_centre_line(mlx, centre + 2, my_dist, color);
// 	return (0);
// }
