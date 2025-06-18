/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_dom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:06:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 21:57:17 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	direction_oriented_movement(t_mlx *mlx);

/* return the 'legal' value of speed */
static float	speed_bound(t_mlx *mlx, int speed)
{
	if (speed > 0 && speed > mlx->player.tspeed[0])
		return (mlx->player.tspeed[0]);
	if (speed < 0 && speed < -mlx->player.tspeed[0])
		return (-mlx->player.tspeed[0]);
	return (speed);
}

/* if the keys relative to the direction aren't pressed,
slowly moves the o_speed towards 0. */
static int	straigthen_o_speed(int *keys, int *o_speed, float friction)
{
	const float	diff = 50 / friction;

	if (*o_speed == 0 || keys[0] != 0 || keys[1] != 0)
		return (0);
	if (*o_speed > 0)
	{
		if (*o_speed - diff > 0)
			(*o_speed) -= diff;
		else
			(*o_speed) = 0;
	}
	if (*o_speed < 0)
	{
		if (*o_speed + diff < 0)
			(*o_speed) += diff;
		else
			(*o_speed) = 0;
	}
	return (1);
}

/* converts o_speed into speed */
static int	o_speed_to_speed(int *o_speed, int *speed, float dir)
{
	const float	x_axis_parallel = cosf(dir * MY_PI / 180);
	const float	y_axis_parallel = sinf(dir * MY_PI / 180);
	const float	x_axis_normal = cosf((dir * MY_PI / 180) - MY_PI_2);
	const float	y_axis_normal = sinf((dir * MY_PI / 180) - MY_PI_2);

	speed[0] = (float)o_speed[0] * x_axis_normal;
	speed[1] = (float)o_speed[0] * y_axis_normal;
	speed[0] += (float)o_speed[1] * x_axis_parallel;
	speed[1] += (float)o_speed[1] * y_axis_parallel;
	return (0);
}

/* changes the speed (player.speed) vector based on the keys
pressed. It's all in one function because I need all the axis together.
This function alone will handle the speed variation on the xOy plane. */
int	direction_oriented_movement(t_mlx *mlx)
{
	int *const	o_speed = mlx->player.o_speed;
	int *const	speed = mlx->player.speed;

	if (mlx->keys.lx_rx[0] == 1)
		o_speed[0] -= 50;
	if (mlx->keys.lx_rx[1] == 1)
		o_speed[0] += 50;
	if (mlx->keys.up_dw[0] == 1)
		o_speed[1] -= 50;
	if (mlx->keys.up_dw[1] == 1)
		o_speed[1] += 50;
	o_speed[0] = speed_bound(mlx, o_speed[0]);
	o_speed[1] = speed_bound(mlx, o_speed[1]);
	straigthen_o_speed(mlx->keys.up_dw, &o_speed[1], mlx->player.friction);
	straigthen_o_speed(mlx->keys.lx_rx, &o_speed[0], mlx->player.friction);
	o_speed_to_speed(o_speed, speed, mlx->player.dir[0]);
	return (0);
}
