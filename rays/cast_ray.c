/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:26:49 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 16:05:39 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

// Normalize the angle to stay within the range [0, 2*PI)
float normalize_dir(float dir)
{
	if (dir < -180)
		return (180 - (-dir - 180));
	else if (dir > 180)
		return (-180 + (dir - 180));
	return (dir);
}

/* casts a ray starting from (x,y) headed for the direction 'dir'
(dir is 0 -> 360). returns the lenght of the ray */
float	cast_ray(t_mlx *mlx, float x, float y, float dir)
{
	const float		angle = dir * M_PI / 180; // 0 = right
	float			incr[2];
	float	*const	ray = mlx->ray.hit;
	int				axis[2];

	mlx->ray.len = -1;
	mlx->ray.face = 'W';

	ray[0] = x;
	ray[1] = y;
	axis[0] = fabsf(angle) > M_PI / 2 ? 1 : -1;
	axis[1] = angle > 0 ? -1 : 1;
	
	// first increment
	incr[0] = axis[0] > 0 ? (int)(ray[0] + 1) : (int)ray[0];
	incr[1] = axis[1] > 0 ? (int)(ray[1] + 1) : (int)ray[1];
	incr[0] = fabsf(ray[0] - (incr[0]));
	incr[1] = fabsf(ray[1] - (incr[1]));

	while (mlx->map.mtx[(int)ray[1]][(int)ray[0]] != '1')
	{
		//ft_printf("start\n");
		if ((/* x +  */incr[0]) / fabsf(cosf(angle))
			< (/* y +  */incr[1]) / fabsf(sinf(angle)))
		{
			//ft_printf("X\n");
			// move trough x ('N', 'S')
			ray[0] = x + incr[0] * axis[0];
			ray[1] = y + incr[0] / fabsf(cosf(angle)) * fabsf(sinf(angle)) * axis[1];
			// checks for collisions
			//ft_printf("low check map[%d, %d]\n", (int)ray[1], (int)ray[0] - 1);
			if (axis[0] < 0 && ((int)ray[0]) > 0 && mlx->map.mtx[(int)ray[1]][(int)ray[0] - 1] == '1')
			{
				mlx->ray.face = 'S';
				break ;
			}
			//ft_printf("high\n");
			if (axis[0] > 0 && ((int)ray[0]) < mlx->map.stats[0] && mlx->map.mtx[(int)ray[1]][((int)ray[0])] == '1')
			{
				mlx->ray.face = 'N';
				break ;
			}
			// modify incr[0]
			incr[0] += 1;
		}
		else
		{
			//ft_printf("Y\n");
			// move trough y ('W', 'E')
			ray[0] = x + incr[1] / fabsf(sinf(angle)) * fabsf(cosf(angle)) * axis[0];
			ray[1] = y + incr[1] * axis[1];
			// checks for collisions
			if (axis[1] < 0 && ((int)ray[1]) > 0 && mlx->map.mtx[((int)ray[1]) - 1][(int)ray[0]] == '1')
			{
				mlx->ray.face = 'E';
				break ;
			}
			if (axis[1] > 0 && ((int)ray[1]) < mlx->map.stats[1] && mlx->map.mtx[(int)ray[1]][((int)ray[0])] == '1')
			{
				mlx->ray.face = 'W';
				break ;
			}
			// modify incr[1]
			incr[1] += 1;
		}
		// /* ft_ */printf("RAY: [%f, %f]\n", ray[0], ray[1]);
		if (ray[0] < 0 || ray[0] >= mlx->map.stats[0]
			|| ray[1] < 0 || ray[1] >= mlx->map.stats[1])
			return (mlx->ray.len);	//flag it big
		//ft_printf("end\n");
	}
	mlx->ray.len = sqrt((ray[0] - x) * (ray[0] - x) + (ray[1] - y) * (ray[1] - y));
	//ft_printf("out\n");
	// just lame second return
	
	//ft_printf("copy ok\n");
	// /* ft_ */printf("============= CONTACT: [%f, %f] ============= \n", ray[0], ray[1]);
	// ft_printf("player (%f, %f)\n", x, y);
	// printf("%f\n", ray[0] - x);
	// printf("%f\n", ray[1] - y);
	return (mlx->ray.len);
}
