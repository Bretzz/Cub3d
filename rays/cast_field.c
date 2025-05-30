/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:07:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/30 18:26:22 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

/* cast one ray for each degree of the FOV */
int	cast_field(t_mlx *mlx, int (*func)(void *, int, float, unsigned int))
{
	const float	delta_dir = (float)mlx->player.fov[0] / MLX_WIN_X;
	float		dir;
	float		len;
	int			i;

	// if (mlx->player.pos[0] < 0 || mlx->player.pos[0])
	// /* ft_ */printf("delta_angle %f\n", delta_dir);
	
	i = -MLX_WIN_X / 2;
	while (i <= MLX_WIN_X / 2)
	{
		dir = normalize_dir(mlx->player.dir[0] + (i * delta_dir));
		// ft_printf("casting ray %i\n", i);
		// ft_printf("field in\n");
		len = cast_ray(mlx, mlx->player.pos[0], mlx->player.pos[1], dir);
		// ft_printf("field out\n");
		// mlx->player.fov[1] = 0;
		if (len > 0)
			len *= cosf((i * delta_dir) * M_PI / 180);
		(*func)(mlx, i + MLX_WIN_X / 2, len, 0xa0b0c0);

		// 2D raycast
		// (*func)(mlx, mlx->map.stats[2], len, 0xa0b0c0);
		i++;
	}
	return (0);
}