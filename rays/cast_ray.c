/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:26:49 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/17 23:13:21 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cast.h"
#include <stdio.h>

/* returns 1 if a collision is found, 0 if it hasn't */
static int	collision_x_check(t_mlx *mlx, int axis)
{
	if ((int)mlx->ray.hit[1] >= mlx->map.stats[1])
		return (0);
	if (axis < 0 && (int)mlx->ray.hit[0] > 0
		&& mlx->map.mtx[(int)mlx->ray.hit[1]][(int)mlx->ray.hit[0] - 1] == '1')
	{
		mlx->ray.face = 'E';
		return (1);
	}
	if (axis > 0 && (int)mlx->ray.hit[0]
		< (int)ft_strlen(mlx->map.mtx[(int)mlx->ray.hit[1]])
		&& mlx->map.mtx[(int)mlx->ray.hit[1]][((int)mlx->ray.hit[0])] == '1')
	{
		mlx->ray.face = 'W';
		return (1);
	}
	return (0);
}

/* ! ! ! CHECK COLLISION ON CORNERS ! ! !
(likely the culprit of the seetrugh corner) */
/* returns 1 if a collision is found, 0 if it hasn't */
static int	collision_y_check(t_mlx *mlx, int axis)
{
	if (axis < 0 && ((int)mlx->ray.hit[1]) > 0
		&& mlx->map.mtx[((int)mlx->ray.hit[1]) - 1]
		[(int)mlx->ray.hit[0]] == '1')
	{
		mlx->ray.face = 'S';
		return (1);
	}
	if (axis > 0 && (int)mlx->ray.hit[1] < mlx->map.stats[1]
		&& (mlx->map.mtx[(int)mlx->ray.hit[1]][((int)mlx->ray.hit[0])] == '1'
		|| ((int)mlx->ray.hit[1] > 0
			&& mlx->map.mtx[(int)mlx->ray.hit[1] - 1]
			[((int)mlx->ray.hit[0])] == '1')))
	{
		mlx->ray.face = 'N';
		return (1);
	}
	return (0);
}

static int	move_trough_y(t_mlx *mlx, t_cast_vars *cast, float x, float y)
{
	cast->ray[0] = x + (cast->incr[1] + cast->iter[1])
		/ fabsf(sinf(cast->angle)) * fabsf(cosf(cast->angle)) * cast->axis[0];
	cast->ray[1] = get_next_border(cast->axis[1], y, cast->iter[1]);
	if (collision_y_check(mlx, cast->axis[1]) != 0)
		return (1);
	cast->iter[1]++;
	return (0);
}

static int	move_trough_x(t_mlx *mlx, t_cast_vars *cast, float x, float y)
{
	cast->ray[0] = get_next_border(cast->axis[0], x, cast->iter[0]);
	cast->ray[1] = y + (cast->incr[0] + cast->iter[0])
		/ fabsf(cosf(cast->angle)) * fabsf(sinf(cast->angle)) * cast->axis[1];
	if (collision_x_check(mlx, cast->axis[0]) != 0)
		return (1);
	cast->iter[0]++;
	return (0);
}

/* casts a ray starting from (x,y) headed for the direction 'dir'
(dir is 0 -> 360). returns the lenght of the ray */
/* NOTE: if the player stands on any square's diagonal point AND a ray
is cast parallel to that diagonal the 'main if' in the while cycle
will result euqals (==) and do the same moves on both move_trough_x() and
move_trough_y() alternatively. So an eventual wall will be hit during
any of the two resoulting in a wall hit accurate only for even/odd
iterations. */
float	cast_ray(t_mlx *mlx, float x, float y, float dir)
{
	t_cast_vars		cast;

	ray_init(&mlx->ray, x, y);
	vars_init(&mlx->ray, &cast, dir);
	if (out_of_bound(mlx, cast.ray))
		return (mlx->ray.len);
	while (mlx->map.mtx[(int)cast.ray[1]][(int)cast.ray[0]] != '1')
	{
		if ((cast.incr[0] + cast.iter[0]) / fabsf(cosf(cast.angle))
			< (cast.incr[1] + cast.iter[1]) / fabsf(sinf(cast.angle)))
		{
			if (move_trough_x(mlx, &cast, x, y) != 0)
				break ;
		}
		else if ((cast.incr[0] + cast.iter[0]) / fabsf(cosf(cast.angle))
			> (cast.incr[1] + cast.iter[1]) / fabsf(sinf(cast.angle)))
		{
			if (move_trough_y(mlx, &cast, x, y) != 0)
				break ;
		}
		else
		{
			// we are going in a diagonal here, do a better check
			// for the wall hit
			if (move_trough_y(mlx, &cast, x, y) != 0)
				break ;
		}
		if (out_of_bound(mlx, cast.ray))
			return (mlx->ray.len);
	}
	mlx->ray.len = sqrt(((cast.ray[0] - x) * (cast.ray[0] - x))
			+ ((cast.ray[1] - y) * (cast.ray[1] - y)));
	return (mlx->ray.len);
}
