/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:26:49 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 00:50:29 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* casts a ray starting from (x,y) headed for the direction 'dir'
(dir is 0 -> 360). returns the lenght of the ray */
float	cast_ray(t_mlx *mlx, float x, float y, int dir)
{
	const float	angle = dir * M_PI / 180; // 0 = right
	float	incr[2];
	float	ray[2];
	int		axis[2];

	ray[0] = x;
	ray[1] = y;
	axis[0] = fabsf(angle) > M_PI / 2 ? 1 : -1;
	axis[1] = angle > 0 ? -1 : 1;
	
	// first increment
	incr[0] = axis[0] > 0 ? (int)(ray[0] + 1) : (int)ray[0];
	incr[1] = axis[1] > 0 ? (int)(ray[1] + 1) : (int)ray[1];
	incr[0] = fabsf(ray[0] - (incr[0]));
	incr[1] = fabsf(ray[1] - (incr[1]));

	while (mlx->map[(int)ray[1]][(int)ray[0]] != '1')
	{
		if ((/* x +  */incr[0]) / fabsf(cosf(angle))
			< (/* y +  */incr[1]) / fabsf(sinf(angle)))
		{
			// move trough x
			ray[0] = x + incr[0] * axis[0];
			ray[1] = y + incr[0] / fabsf(cosf(angle)) * fabsf(sinf(angle)) * axis[1];
			// checks for collisions
			if (axis[0] < 0 && ((int)ray[0]) > 0 && mlx->map[(int)ray[1]][((int)ray[0]) - 1] == '1')
				break ;
			if (axis[0] > 0 && ((int)ray[0]) < mlx->map_dim[0] && mlx->map[(int)ray[1]][((int)ray[0])] == '1')
				break ;
			// modify incr[0]
			incr[0] += 1;
		}
		else
		{
			// move trough y
			ray[0] = x + incr[1] / fabsf(sinf(angle)) * fabsf(cosf(angle)) * axis[0];
			ray[1] = y + incr[1] * axis[1];
			// checks for collisions
			if (axis[1] < 0 && ((int)ray[1]) > 0 && mlx->map[((int)ray[1]) - 1][(int)ray[0]] == '1')
				break ;
			if (axis[1] > 0 && ((int)ray[1]) < mlx->map_dim[1] && mlx->map[(int)ray[1]][((int)ray[0])] == '1')
				break ;
			// modify incr[1]
			incr[1] += 1;
		}
		// ft_printf("RAY: [%d, %d]\n", ray[0], ray[1]);
		if (ray[0] < 0 || ray[0] >= mlx->map_dim[0]
			|| ray[1] < 0 || ray[1] >= mlx->map_dim[1])
			return (-1);	//flag it big
	}

	// just lame second return
	if (mlx->player.fov[1] != 0)
		ft_memcpy(mlx->ray, ray, 2 * sizeof(float));
		
	// ft_printf("%d intersection: [%d, %d]\n", i, ray[0], ray[1]);
	return (sqrt(pow(ray[0] - x, 2) + pow(ray[1] - y, 2)));
}
