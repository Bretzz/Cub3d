/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:00:23 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/08 17:45:13 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cast.h"

float	normalize_dir(float dir);

void	ray_init(t_ray *ray, float x, float y);
void	vars_init(t_ray *ray, t_cast_vars *cast, float dir);
int		out_of_bound(t_mlx *mlx, float *ray);
int		get_next_border(int axis, float start, int i);

// Normalize the direction to stay within the range [-180, 180]
float	normalize_dir(float dir)
{
	if (dir <= -180)
		return (180 - (-dir - 180));
	else if (dir > 180)
		return (-180 + (dir - 180));
	return (dir);
}

/* initializes the ray's data */
void	ray_init(t_ray *ray, float x, float y)
{
	ft_memset(ray, 0, sizeof(t_ray));
	ray->hit[0] = x;
	ray->hit[1] = y;
	ray->len = -1;
	ray->face = 'V';
}

/* initializes the first increment */
/* NOTE: ray->hit must be already initialized */
void	vars_init(t_ray *ray, t_cast_vars *cast, float dir)
{
	ft_memset(cast, 0, sizeof(t_cast_vars));
	cast->ray = ray->hit;
	cast->angle = dir * M_PI / 180;
	if (fabsf(cast->angle) > M_PI / 2)
	{
		cast->axis[0] = 1;
		cast->incr[0] = (int)(ray->hit[0]) + 1;
	}
	else
	{
		cast->axis[0] = -1;
		cast->incr[0] = (int)(ray->hit[0]);
	}
	if (cast->angle < 0)
	{
		cast->axis[1] = 1;
		cast->incr[1] = (int)(ray->hit[1]) + 1;
	}
	else
	{
		cast->axis[1] = -1;
		cast->incr[1] = (int)(ray->hit[1]);
	}
	cast->incr[0] = fabsf(ray->hit[0] - cast->incr[0]);
	cast->incr[1] = fabsf(ray->hit[1] - cast->incr[1]);
}

/* returns the value of the next border found based on axis */
int	get_next_border(int axis, float start, int i)
{
	if (axis > 0)
		return ((int)start + i + 1);
	return ((int)start - i);
}

/* checks if the ray is out ouf bounds :D */
int	out_of_bound(t_mlx *mlx, float *ray)
{
	if (ray[1] <= 0
		|| (int)ray[1] >= mlx->map.stats[1]
		|| ray[0] <= 0
		|| (int)ray[0] >= (int)ft_strlen(mlx->map.mtx[(int)ray[1]]))
		return (1);
	return (0);
}
