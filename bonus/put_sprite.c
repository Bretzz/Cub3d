/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:59:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 20:35:59 by topiana-         ###   ########.fr       */
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
	const float sprite_dir = atan2((my_pos[1] - y), (my_pos[0] - x)) * 180 / M_PI;
	const int	mid_line = cos(mlx->player.dir[1] * M_PI / 180) * (2 * mlx->win_y) + (mlx->win_y / 2);
	float		my_dist;
	// visibility check
	if (sprite_dir < mlx->player.dir[0] - (mlx->player.fov[0] / 2)
	|| sprite_dir > mlx->player.dir[0] + (mlx->player.fov[0] / 2))
		return (1);
	// obstacle check
	// ft_printf("casting sprite ray... ");
	cast_ray(mlx, my_pos[0], my_pos[1], sprite_dir);
	// ft_printf("done\n");
	my_dist = sqrt(pow(x - my_pos[0], 2) + pow(y - my_pos[1], 2));
	// ft_printf("sprint inside the fov\n");
	if (mlx->ray.len > 0 && mlx->ray.len < my_dist)
		return (1);
	// /* ft_ */printf("SEEING SPRITE: dir %f\n", sprite_dir);
	int x_screen = (mlx->win_x / 2) + (sprite_dir - mlx->player.dir[0]) * (mlx->win_x / mlx->player.fov[0]);
	// /* ft_ */printf("sprite on x_screen %d, diff dir %f\n", x_screen, (sprite_dir - mlx->player.dir[0]));
	// put_square(mlx, 10, x_screen, mlx->win_y / 2, color);
	// ft_printf("putting sprite... ");
	put_sprite(mlx, x_screen, mid_line, ((mlx->win_x / 2) / mlx->player.sprite_y) / my_dist);
	// ft_printf("done\n");
	(void)color;
	return (0);
}
