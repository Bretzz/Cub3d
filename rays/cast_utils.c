/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:00:23 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 17:17:26 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cast.h"

float	normalize_dir(float dir);

void	ray_init(t_ray *ray, float x, float y);
void	vars_init(t_ray *ray, t_cast_vars *cast, float dir);
int		out_of_bound(t_mlx *mlx, t_cast_vars *cast, float x, float y);

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

static void	angle_init(t_cast_vars *cast, float dir)
{
	cast->angle = (float)dir * (M_PI / 180.0f);
	cast->cos_angle = fabsf(cosf(cast->angle));
	cast->sin_angle = fabsf(sinf(cast->angle));
	cast->inv_cos = 1.0f / cast->cos_angle;
	cast->inv_sin = 1.0f / cast->sin_angle;
}

/* initializes the first increment */
/* NOTE: ray->hit must be already initialized */
void	vars_init(t_ray *ray, t_cast_vars *cast, float dir)
{
	ft_memset(cast, 0, sizeof(t_cast_vars));
	angle_init(cast, dir);
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

/* checks if the ray is out ouf bounds :D */
int	out_of_bound(t_mlx *mlx, t_cast_vars *cast, float x, float y)
{
	const int	curr_x = (int)x + cast->axis[0] * cast->iter[0];
	const int	curr_y = (int)y + cast->axis[1] * cast->iter[1];

	if (curr_y < 0
		|| curr_y >= mlx->map.stats[1]
		|| curr_x < 0
		|| curr_x >= mlx->map.stats[0])
		return (1);
	return (0);
}
