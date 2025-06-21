/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:07:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/21 19:26:42 by scarlucc         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"
#include <stdio.h>

/* 2D raycast: (*func)(mlx, mlx->map.stats[2], len, 0xa0b0c0); */
/* cast one ray for pixel on the x-axis of the screen */
int	cast_field(t_mlx *mlx,
	int (*func3d)(void *, int, float),
	int (*func2d)(void *, int, float, unsigned int))
{
	const float	delta_dir = (float)mlx->player.fov[0] / MLX_WIN_X;
	const int	half_win = MLX_WIN_X / 2;
	float		dir;
	float		len;
	int			i;

	i = -half_win;
	while (i <= half_win)
	{
		dir = normalize_dir(mlx->player.dir[0] + (i * delta_dir));
		len = cast_ray(mlx, mlx->player.pos[0], mlx->player.pos[1], dir);
		if (len > 0.0f)
			len *= cosf((i * delta_dir) * (float)(MY_PI / 180.0f));
		if (func3d)
			(*func3d)(mlx, i + MLX_WIN_X / 2, len);
		if (func2d)
			(*func2d)(mlx, mlx->map.mini_side, len, RAY_COLOR);
		i++;
	}
	return (0);
}
