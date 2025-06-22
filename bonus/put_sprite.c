/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:16:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 17:20:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* adds the sprite to the mlx->img
starting from x_screen and y_screen and scaled
by a factor (scale).
NOTE: future implementation: passing the sprite pointer and the
dimensions of the sprite. */
/* dunno how color < 100000000 excludes 'None' of xpm */
void	put_sprite(t_mlx *mlx, t_plot plot, t_sprite sprite)
{
	const int			new_width = (sprite.width * sprite.scale);
	const int			new_height = (sprite.height * sprite.scale);
	int					win_x_y[2];
	int					src_x_y[2];
	unsigned int		color;

	win_x_y[1] = 0;
	while (win_x_y[1] < new_height && win_x_y[1]
		+ (plot.y_screen - (new_height / 2)) < MLX_WIN_Y)
	{
		win_x_y[0] = 0;
		while (win_x_y[0] < new_width && win_x_y[0]
			+ (plot.x_screen - (new_width / 2)) < MLX_WIN_X)
		{
			src_x_y[0] = win_x_y[0] * sprite.width / new_width;
			src_x_y[1] = win_x_y[1] * sprite.height / new_height;
			color = get_pixel_color(sprite.image, src_x_y[0], src_x_y[1]);
			if ((unsigned int)color < 100000000)
				my_pixel_put(&mlx->img,
					win_x_y[0] + (plot.x_screen - (new_width / 2)),
					win_x_y[1] + (plot.y_screen - (new_height / 2)), color);
			win_x_y[0]++;
		}
		win_x_y[1]++;
	}
}
