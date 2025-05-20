/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sky_floor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:54:49 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 16:55:08 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* update the color */
int	put_sky_floor(t_mlx *mlx)
{
	const int		mid_line = sin(mlx->player.dir[1] * M_PI / 180) * (2 * mlx->win_y) + (mlx->win_y / 2);
	int	pixel[2];

	pixel[1] = 0;
	while (pixel[1] < mlx->win_y)
	{
		pixel[0] = 0;
		while (pixel[0] < mlx->win_x)
		{
			if (pixel[1] < mid_line)
				my_pixel_put(mlx, pixel[0], pixel[1], 0xadd8e6);
			else
				my_pixel_put(mlx, pixel[0], pixel[1], 0xcaf0d5);
			pixel[0]++;
		}
		pixel[1]++;
	}
	return (0);
}
