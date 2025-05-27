/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:07:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/27 23:54:30 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

/* cast one ray for each degree of the FOV */
int	cast_field(t_mlx *mlx, int (*func)(void *, int, float, unsigned int))
{
	const float	delta_dir = (float)mlx->player.fov[0] / mlx->win_x;
	float		dir;
	float		len;
	int			i;

	// if (mlx->player.pos[0] < 0 || mlx->player.pos[0])
	// /* ft_ */printf("delta_angle %f\n", delta_dir);
	
	i = -mlx->win_x / 2;
	while (i <= mlx->win_x / 2)
	{
		dir = normalize_dir(mlx->player.dir[0] + (i * delta_dir));
		// ft_printf("casting ray %i\n", i);
		// ft_printf("field in\n");
		len = cast_ray(mlx, mlx->player.pos[0], mlx->player.pos[1], dir);
		// ft_printf("field out\n");
		// mlx->player.fov[1] = 0;
		if (len > 0)
			len *= cosf((i * delta_dir) * M_PI / 180);
		if (i != 0)
			// (*func)(mlx, mlx->map.stats[2], len, 0xa0b0c0);
			(*func)(mlx, i + mlx->win_x / 2, len, 0xa0b0c0);
		else	//central ray
			(*func)(mlx, i + mlx->win_x / 2, len, 0xa0bff);

		// /* ft_ */printf("casting pixel %d, with angle %f, got len %f\n", i, dir * M_PI / 180, len);
		//put_centre_line(mlx, i + mlx->win_x / 2, len, 0xff0000);
			// (*func)(mlx, mlx->map_dim[2], len, 0xa0b0c0);
		i++;
	}
	return (0);
}