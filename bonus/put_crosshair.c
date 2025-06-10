/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_crosshair.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:12:46 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/10 12:49:07 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	put_crosshair(t_mlx *mlx, unsigned int color);

int	put_crosshair(t_mlx *mlx, unsigned int color)
{
	const int	len[2] = {10, 10};
	int			pixel[2];

	pixel[1] = MLX_WIN_Y / 2;
	pixel[0] = (MLX_WIN_X / 2) - len[0];
	while (pixel[0] < (MLX_WIN_X / 2) + len[0])
	{
		my_pixel_put(&mlx->img, pixel[0], pixel[1], color);
		pixel[0]++;
	}
	pixel[0] = MLX_WIN_X / 2;
	pixel[1] = (MLX_WIN_Y / 2) - len[1];
	while (pixel[1] < (MLX_WIN_Y / 2) + len[1])
	{
		my_pixel_put(&mlx->img, pixel[0], pixel[1], color);
		pixel[1]++;
	}
	return (0);
}

// 800 200 200
// 760 250 150