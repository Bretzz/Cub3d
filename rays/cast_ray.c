/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:26:49 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 03:11:04 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cast.h"
#include <stdio.h>

// welp...
static char	get_smart_face(char x_or_y, int axis)
{
	if (x_or_y == 1)
	{
		if (axis > 0)
			return ('N');
		else
			return ('S');
	}
	else if (x_or_y == 0)
	{
		if (axis > 0)
			return ('W');
		else
			return ('E');
	}
	return ('V');
}

void	get_x_collision(t_mlx *mlx, t_cast_vars *cast, float x, float y)
{
	mlx->ray.hit[0] = x + (cast->iter[0] - 1 + cast->incr[0]) * cast->axis[0];
	mlx->ray.hit[1] = y + (cast->incr[0] + cast->iter[0] - 1)
		/ fabsf(cosf(cast->angle)) * fabsf(sinf(cast->angle)) * cast->axis[1];
}

void	get_y_collision(t_mlx *mlx, t_cast_vars *cast, float x, float y)
{
	mlx->ray.hit[1] = y + (cast->iter[1] - 1 + cast->incr[1]) * cast->axis[1];
	mlx->ray.hit[0] = x + (cast->incr[1] + cast->iter[1] - 1)
		/ fabsf(sinf(cast->angle)) * fabsf(cosf(cast->angle)) * cast->axis[0];
}

// needs to be called every cycle
static int	collision_check(t_mlx *mlx, t_cast_vars *cast, float x, float y)
{
	int			curr_x;
	int			curr_y;

	curr_x = (int)x + cast->axis[0] * cast->iter[0];
	curr_y = (int)y + cast->axis[1] * cast->iter[1];
	if (mlx->map.mtx[curr_y][curr_x] == '1') 
		return (1);
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
	while (!out_of_bound(mlx, &cast, x, y))
	{
		if ((cast.incr[0] + cast.iter[0]) / fabsf(cosf(cast.angle))
			< (cast.incr[1] + cast.iter[1]) / fabsf(sinf(cast.angle)))
		{
			cast.iter[0]++;
			cast.curr = 0;
		}
		// else if ((cast.incr[0] + cast.iter[0]) / fabsf(cosf(cast.angle))
		// 	> (cast.incr[1] + cast.iter[1]) / fabsf(sinf(cast.angle)))
		// {
		// 	cast.iter[1]++;
		// 	cast.curr = 1;
		// }
		else
		{
			cast.iter[1]++;
			cast.curr = 1;
		}
		if (collision_check(mlx, &cast, x, y))
		{
			mlx->ray.face = get_smart_face(cast.curr, cast.axis[cast.curr]);
			break ;
		}
	}
	if (cast.curr == 0)
		get_x_collision(mlx, &cast, x, y);
	else
		get_y_collision(mlx, &cast, x, y);
	mlx->ray.len = sqrt(((mlx->ray.hit[0] - x) * (mlx->ray.hit[0] - x))
			+ ((mlx->ray.hit[1] - y) * (mlx->ray.hit[1] - y)));
	return (mlx->ray.len);
}
