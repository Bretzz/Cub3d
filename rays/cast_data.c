/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:47:06 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 16:15:02 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cast.h"

void	get_ray_data(t_mlx *mlx, t_cast_vars *cast, float x, float y);

static void	get_x_collision(t_mlx *mlx, t_cast_vars *cast, float x, float y)
{
	const float	step = cast->incr[0] + cast->iter[0] - 1;
	const float	offset = step * cast->inv_cos * cast->sin_angle * cast->axis[1];

	mlx->ray.hit[0] = x + step * cast->axis[0];
	mlx->ray.hit[1] = y + offset;
}

static void	get_y_collision(t_mlx *mlx, t_cast_vars *cast, float x, float y)
{
	const float	step = cast->incr[1] + cast->iter[1] - 1;
	const float	offset = step * cast->inv_sin * cast->cos_angle * cast->axis[0];

	mlx->ray.hit[1] = y + step * cast->axis[1];
	mlx->ray.hit[0] = x + offset;
}

void	get_ray_data(t_mlx *mlx, t_cast_vars *cast, float x, float y)
{
	float	dx;
	float	dy;

	if (cast->curr != 0)
		get_y_collision(mlx, cast, x, y);
	else
		get_x_collision(mlx, cast, x, y);
	if (mlx->ray.face == 'V')
		return ;
	dx = mlx->ray.hit[0] - x;
	dy = mlx->ray.hit[1] - y;
	mlx->ray.len = sqrtf(dx * dx + dy * dy);
}
