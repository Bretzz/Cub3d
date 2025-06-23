/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:47:06 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/23 12:11:07 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cast.h"

#define FLOAT_TOLERANCE 0.00001f

static float	ft_roundf(float f)
{
	if ((int)(f + FLOAT_TOLERANCE) != (int)f)
		return (f + FLOAT_TOLERANCE);
	if ((int)(f - FLOAT_TOLERANCE) != (int)f)
		return (f - FLOAT_TOLERANCE);
	return (f);
}

void	get_ray_data(t_mlx *mlx, t_cast_vars *cast, float x, float y);

static void	get_x_collision(t_mlx *mlx, t_cast_vars *cast, float x, float y)
{
	const float	step = cast->incr[0] + cast->iter[0] - 1;
	const float	offset = step * cast->inv_cos * cast->sin_angle * cast->axis[1];

	mlx->ray.hit[0] = ft_roundf(x + step * cast->axis[0]);
	mlx->ray.hit[1] = ft_roundf(y + offset);
}

static void	get_y_collision(t_mlx *mlx, t_cast_vars *cast, float x, float y)
{
	const float	step = cast->incr[1] + cast->iter[1] - 1;
	const float	offset = step * cast->inv_sin * cast->cos_angle * cast->axis[0];

	mlx->ray.hit[1] = ft_roundf(y + step * cast->axis[1]);
	mlx->ray.hit[0] = ft_roundf(x + offset);
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
