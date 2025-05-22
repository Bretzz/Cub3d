/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:26:49 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/22 15:13:22 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

// Normalize the direction to stay within the range [-180, 180]
float normalize_dir(float dir)
{
	if (dir < -180)
		return (180 - (-dir - 180));
	else if (dir > 180)
		return (-180 + (dir - 180));
	return (dir);
}

/* initializes the first increment */
/* NOTE: ray->hit must be already initialized */
/* static  */void	ray_init(t_ray *ray, float *incr, int *axis, const float angle)
{
	ray->len = -1;
	ray->face = 'V';
	if (fabsf(angle) > M_PI / 2)
	{
		axis[0] = 1;
		incr[0] = (int)(ray->hit[0]) + 1;
	}
	else
	{
		axis[0] = -1;
		incr[0] = (int)(ray->hit[0]);
	}
	if (angle < 0)
	{
		axis[1] = 1;
		incr[1] = (int)(ray->hit[1]) + 1;
	}
	else
	{
		axis[1] = -1;
		incr[1] = (int)(ray->hit[1]);
	}
	incr[0] = fabsf(ray->hit[0] - (incr[0]));
	incr[1] = fabsf(ray->hit[1] - (incr[1]));
}

/* returns 1 if a collision is found, 0 if it hasn't */
/* static  */int	collision_x_check(t_mlx *mlx, int axis)
{
	if (axis < 0 && ((int)mlx->ray.hit[0]) > 0
		&& mlx->map.mtx[(int)mlx->ray.hit[1]][(int)mlx->ray.hit[0] - 1] == '1')
	{
		mlx->ray.face = 'E';
		return (1) ;
	}
	if (axis > 0 && ((int)mlx->ray.hit[0])
		< (int)ft_strlen(mlx->map.mtx[(int)mlx->ray.hit[1]])
		&& mlx->map.mtx[(int)mlx->ray.hit[1]][((int)mlx->ray.hit[0])] == '1')
	{
		mlx->ray.face = 'W';
		return (1) ;
	}
	return (0);
}

/* returns 1 if a collision is found, 0 if it hasn't */
/* static  */int	collision_y_check(t_mlx *mlx, int axis)
{
	if (axis < 0 && ((int)mlx->ray.hit[1]) > 0
		&& mlx->map.mtx[((int)mlx->ray.hit[1]) - 1][(int)mlx->ray.hit[0]] == '1')
	{
		mlx->ray.face = 'S';
		return (1) ;
	}
	if (axis > 0 && ((int)mlx->ray.hit[1]) < mlx->map.stats[1]
		&& mlx->map.mtx[(int)mlx->ray.hit[1]][((int)mlx->ray.hit[0])] == '1')
	{
		mlx->ray.face = 'N';
		return(1) ;
	}
	return (0);
}

/* casts a ray starting from (x,y) headed for the direction 'dir'
(dir is 0 -> 360). returns the lenght of the ray */
float	cast_ray(t_mlx *mlx, float x, float y, float dir)
{
	const float		angle = dir * M_PI / 180; // 0 = right
	float			incr[2];
	float	*const	ray = mlx->ray.hit;
	int				axis[2];
	unsigned int	i[2];

	ray[0] = x;
	ray[1] = y;
	ray_init(&mlx->ray, incr, axis, angle);
	ft_memset(i, 0, 2 * sizeof(int));
	while (mlx->map.mtx[(int)ray[1]][(int)ray[0]] != '1')
	{
		//ft_printf("start\n");
		if ((incr[0]+ i[0]) / fabsf(cosf(angle))
			< (incr[1]+ i[1]) / fabsf(sinf(angle)))
		{
			if (mlx->player.sprite_x > 32) {ft_printf("X\n");}
			// move trough x ('E', 'W')
			ray[0] = axis[0] > 0 ? (int)x + i[0] + 1 : (int)x - i[0];
			ray[1] = y + (incr[0]+ i[0]) / fabsf(cosf(angle)) * fabsf(sinf(angle)) * axis[1];
			// checks for collisions
			if (collision_x_check(mlx, axis[0]) != 0)
				break ;
			// incr[0] += 1;
			i[0]++;
		}
		else
		{
			if (mlx->player.sprite_x > 32) {ft_printf("Y\n");}
			// move trough y ('N', 'S')
			ray[0] = x + (incr[1]+ i[1]) / fabsf(sinf(angle)) * fabsf(cosf(angle)) * axis[0];
			ray[1] = axis[1] > 0 ? (int)y + i[1] + 1 : (int)y - i[1];
			// checks for collisions
			if (collision_y_check(mlx, axis[1]) != 0)
				break ;
			// incr[1] += 1;
			i[1]++;
		}
		if (mlx->player.sprite_x > 32) {/* ft_ */printf("RAY: [%f, %f]\n", ray[0], ray[1]);}
		if (ray[1] < 0 || ray[1] >= mlx->map.stats[1]
			|| ray[0] < 0 || ray[0] >= (int)ft_strlen(mlx->map.mtx[(int)ray[1]]))
			return (mlx->ray.len);
		//ft_printf("end\n");
	}
	mlx->ray.len = sqrt(((ray[0] - x) * (ray[0] - x)) + ((ray[1] - y) * (ray[1] - y)));
	//ft_printf("out\n");
	// just lame second return
	
	//ft_printf("copy ok\n");
	if (mlx->player.sprite_x > 32) {/* ft_ */printf("============= %c: [%f, %f] ============= \n", mlx->ray.face, ray[0], ray[1]);}
	return (mlx->ray.len);
}

/* casts a ray starting from (x,y) headed for the direction 'dir'
(dir is 0 -> 360). returns the lenght of the ray */
// float	cast_ray(t_mlx *mlx, float x, float y, float dir)
// {
// 	const float		angle = dir * M_PI / 180; // 0 = right
// 	float			incr[2];
// 	float	*const	ray = mlx->ray.hit;
// 	int				axis[2];

// 	ray[0] = x;
// 	ray[1] = y;
// 	ray_init(&mlx->ray, incr, axis, angle);
// 	// axis[0] = fabsf(angle) > M_PI / 2 ? 1 : -1;
// 	// axis[1] = angle > 0 ? -1 : 1;
	
// 	// // first increment
// 	// incr[0] = axis[0] > 0 ? (int)(ray[0] + 1) : (int)ray[0];
// 	// incr[1] = axis[1] > 0 ? (int)(ray[1] + 1) : (int)ray[1];
// 	// incr[0] = fabsf(ray[0] - (incr[0]));
// 	// incr[1] = fabsf(ray[1] - (incr[1]));

// 	while (mlx->map.mtx[(int)ray[1]][(int)ray[0]] != '1')
// 	{
// 		//ft_printf("start\n");
// 		if ((/* x +  */incr[0]) / fabsf(cosf(angle))
// 			< (/* y +  */incr[1]) / fabsf(sinf(angle)))
// 		{
// 			if (mlx->player.sprite_x > 32) {ft_printf("X\n");}
// 			// move trough x ('E', 'W')
// 			// ray[0] = x + incr[0] * axis[0];
// 			ray[0] = axis[0] > 0 ? (int)x + (int)incr[0] + 1 : (int)x - (int)incr[0];
// 			ray[1] = y + incr[0] / fabsf(cosf(angle)) * fabsf(sinf(angle)) * axis[1];
// 			// checks for collisions
// 			//ft_printf("low check map[%d, %d]\n", (int)ray[1], (int)ray[0] - 1);
// 			if (collision_x_check(mlx, axis[0]) != 0)
// 				break ;
// 			// modify incr[0]
// 			incr[0] += 1;
// 		}
// 		else
// 		{
// 			if (mlx->player.sprite_x > 32) {ft_printf("Y\n");}
// 			// move trough y ('N', 'S')
// 			ray[0] = x + incr[1] / fabsf(sinf(angle)) * fabsf(cosf(angle)) * axis[0];
// 			ray[1] = axis[1] > 0 ? (int)y + (int)incr[1] + 1 : (int)y - (int)incr[1];
// 			// ray[1] = y + incr[1] * axis[1];
// 			// checks for collisions
// 			if (collision_y_check(mlx, axis[1]) != 0)
// 				break ;
// 			// modify incr[1]
// 			incr[1] += 1;
// 		}
// 		if (mlx->player.sprite_x > 32) {/* ft_ */printf("RAY: [%f, %f]\n", ray[0], ray[1]);}
// 		if (ray[1] < 0 || ray[1] >= mlx->map.stats[1]
// 			|| ray[0] < 0 || ray[0] >= (int)ft_strlen(mlx->map.mtx[(int)ray[1]]))
// 			return (mlx->ray.len);	//flag it big
// 		//ft_printf("end\n");
// 	}
// 	mlx->ray.len = sqrt((ray[0] - x) * (ray[0] - x) + (ray[1] - y) * (ray[1] - y));
// 	//ft_printf("out\n");
// 	// just lame second return
	
// 	//ft_printf("copy ok\n");
// 	if (mlx->player.sprite_x > 32) {/* ft_ */printf("============= %c: [%f, %f] ============= \n", mlx->ray.face, ray[0], ray[1]);}
// 	// ft_printf("player (%f, %f)\n", x, y);
// 	// printf("%f\n", ray[0] - x);
// 	// printf("%f\n", ray[1] - y);
// 	return (mlx->ray.len);
// }




/* = = == === ! ! ! ORIGINAL ! ! ! ===== = == = */
// /* casts a ray starting from (x,y) headed for the direction 'dir'
// (dir is 0 -> 360). returns the lenght of the ray */
// float	cast_ray(t_mlx *mlx, float x, float y, float dir)
// {
// 	const float		angle = dir * M_PI / 180; // 0 = right
// 	float			incr[2];
// 	float	*const	ray = mlx->ray.hit;
// 	int				axis[2];

// 	ray[0] = x;
// 	ray[1] = y;
// 	axis[0] = fabsf(angle) > M_PI / 2 ? 1 : -1;
// 	axis[1] = angle > 0 ? -1 : 1;
	
// 	// first increment
// 	incr[0] = axis[0] > 0 ? (int)(ray[0] + 1) : (int)ray[0];
// 	incr[1] = axis[1] > 0 ? (int)(ray[1] + 1) : (int)ray[1];
// 	incr[0] = fabsf(ray[0] - (incr[0]));
// 	incr[1] = fabsf(ray[1] - (incr[1]));

// 	while (mlx->map.mtx[(int)ray[1]][(int)ray[0]] != '1')
// 	{
// 		//ft_printf("start\n");
// 		if ((/* x +  */incr[0]) / fabsf(cosf(angle))
// 			< (/* y +  */incr[1]) / fabsf(sinf(angle)))
// 		{
// 			if (mlx->player.sprite_x > 32) {ft_printf("X\n");}
// 			// move trough x ('E', 'W')
// 			// ray[0] = x + incr[0] * axis[0];
// 			ray[0] = axis[0] > 0 ? (int)x + (int)incr[0] + 1 : (int)x - (int)incr[0];
// 			ray[1] = y + incr[0] / fabsf(cosf(angle)) * fabsf(sinf(angle)) * axis[1];
// 			// checks for collisions
// 			//ft_printf("low check map[%d, %d]\n", (int)ray[1], (int)ray[0] - 1);
// 			if (axis[0] < 0 && ((int)ray[0]) > 0 && mlx->map.mtx[(int)ray[1]][(int)ray[0] - 1] == '1')
// 			{
// 				mlx->ray.face = 'E';
// 				break ;
// 			}
// 			//ft_printf("high\n");
// 			if (axis[0] > 0 && ((int)ray[0]) < (int)ft_strlen(mlx->map.mtx[(int)ray[1]]) && mlx->map.mtx[(int)ray[1]][((int)ray[0])] == '1')
// 			{
// 				mlx->ray.face = 'W';
// 				break ;
// 			}
// 			// modify incr[0]
// 			incr[0] += 1;
// 		}
// 		else
// 		{
// 			if (mlx->player.sprite_x > 32) {ft_printf("Y\n");}
// 			// move trough y ('N', 'S')
// 			ray[0] = x + incr[1] / fabsf(sinf(angle)) * fabsf(cosf(angle)) * axis[0];
// 			ray[1] = axis[1] > 0 ? (int)y + (int)incr[1] + 1 : (int)y - (int)incr[1];
// 			// ray[1] = y + incr[1] * axis[1];
// 			// checks for collisions
// 			if (axis[1] < 0 && ((int)ray[1]) > 0 && mlx->map.mtx[((int)ray[1]) - 1][(int)ray[0]] == '1')
// 			{
// 				mlx->ray.face = 'S';
// 				break ;
// 			}
// 			if (axis[1] > 0 && ((int)ray[1]) < mlx->map.stats[1] && mlx->map.mtx[(int)ray[1]][((int)ray[0])] == '1')
// 			{
// 				mlx->ray.face = 'N';
// 				break ;
// 			}
// 			// modify incr[1]
// 			incr[1] += 1;
// 		}
// 		if (mlx->player.sprite_x > 32) {/* ft_ */printf("RAY: [%f, %f]\n", ray[0], ray[1]);}
// 		if (ray[1] < 0 || ray[1] >= mlx->map.stats[1]
// 			|| ray[0] < 0 || ray[0] >= (int)ft_strlen(mlx->map.mtx[(int)ray[1]]))
// 			return (mlx->ray.len);	//flag it big
// 		//ft_printf("end\n");
// 	}
// 	mlx->ray.len = sqrt((ray[0] - x) * (ray[0] - x) + (ray[1] - y) * (ray[1] - y));
// 	//ft_printf("out\n");
// 	// just lame second return
	
// 	//ft_printf("copy ok\n");
// 	if (mlx->player.sprite_x > 32) {/* ft_ */printf("============= %c: [%f, %f] ============= \n", mlx->ray.face, ray[0], ray[1]);}
// 	// ft_printf("player (%f, %f)\n", x, y);
// 	// printf("%f\n", ray[0] - x);
// 	// printf("%f\n", ray[1] - y);
// 	return (mlx->ray.len);
// }

