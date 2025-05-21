/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sky_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:48:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 22:25:55 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* update the color */
int	put_sky_floor(t_mlx *mlx)
{
	int	pixel[2];

	pixel[1] = 0;
	while (pixel[1] < mlx->win_y)
	{
		pixel[0] = 0;
		while (pixel[0] < mlx->win_x)
		{
			if (pixel[1] < mlx->win_y / 2)
				my_pixel_put(mlx, pixel[0], pixel[1], mlx->map.sky);
			else
				my_pixel_put(mlx, pixel[0], pixel[1], mlx->map.floor);
			pixel[0]++;
		}
		pixel[1]++;
	}
	return (0);
}
