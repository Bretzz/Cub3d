/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:47:19 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/26 22:57:58 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DIST_MIN 0.01f
#define	DELTA_SPEED 0.001f

int	move_player(t_mlx *mlx);

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
	const float	diff = 50 * friction;

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
	const float	x_axis_parallel = cosf(dir * M_PI / 180);
	const float	y_axis_parallel = sinf(dir * M_PI / 180);
	const float	x_axis_normal = cosf((dir * M_PI / 180) - M_PI_2);
	const float	y_axis_normal = sinf((dir * M_PI / 180) - M_PI_2);

	// printf("o_speed (%d, %d) | axis_normal x: %f, y: %f\n", o_speed[0], o_speed[1], x_axis_normal, y_axis_normal);
	speed[0] = (float)o_speed[0] * /* DELTA_SPEED *  */x_axis_normal;
	speed[1] = (float)o_speed[0] * /* DELTA_SPEED *  */y_axis_normal;
	speed[0] += (float)o_speed[1] * /* DELTA_SPEED *  */x_axis_parallel;
	speed[1] += (float)o_speed[1] * /* DELTA_SPEED *  */y_axis_parallel;
	return (0);
}

/* changes the speed (player.speed) vector based on the keys
pressed. It's all in one function because I need all the axis together. */
static int	direction_oriented_movement(t_mlx *mlx)
{
	int *const	o_speed = mlx->player.o_speed;
	int *const	speed = mlx->player.speed;
	if (mlx->key_lx_rx[0] == 1)
		o_speed[0] -= 50;
	if (mlx->key_lx_rx[1] == 1)
		o_speed[0] += 50;
	if (mlx->key_up_dw[0] == 1)
		o_speed[1] -= 50;
	if (mlx->key_up_dw[1] == 1)
		o_speed[1] += 50;
	o_speed[0] = speed_bound(mlx, o_speed[0]);
	o_speed[1] = speed_bound(mlx, o_speed[1]);
	straigthen_o_speed(mlx->key_up_dw, &o_speed[1], mlx->player.friction);
	straigthen_o_speed(mlx->key_lx_rx, &o_speed[0], mlx->player.friction);
	// ft_printf("o_speed (%d, %d)\n", o_speed[0], o_speed[1]);
	o_speed_to_speed(o_speed, speed, mlx->player.dir[0]);
	// printf("speed (%d, %d)\n", speed[0], speed[1]);
	return (0);
}

/* moves the player (.pos) based on the speed (.speed)
NOTE: it's the only place where we change player.pos' values */
int	move_and_slide(t_local *player, t_map map)
{
	const int	x_max = ft_strlen(map.mtx[(int)player->pos[1]]);
	const float	x_speed = player->speed[0] * DELTA_SPEED;
	const float	y_speed = player->speed[1] * DELTA_SPEED;

	// x-limits [0, map-size]
	if (player->pos[0] + x_speed > x_max)
	{
		player->pos[0] = x_max - DIST_MIN;
		player->speed[0] = 0;
	}
	else if (player->pos[0] + x_speed < 0)
	{
		player->pos[0] = 0 + DIST_MIN;
		player->speed[0] = 0;
	}
	else
		player->pos[0] += x_speed;

	// y-limits [0, map-size]
	if (player->pos[1] + y_speed > map.stats[1])
	{
		player->pos[1] = map.stats[1] - DIST_MIN;
		player->speed[1] = 0;
	}
	else if (player->pos[1] + y_speed < 0)
	{
		player->pos[1] = 0 + DIST_MIN;
		player->speed[1] = 0;
	}
	else
		player->pos[1] += y_speed;
	return (0);
}

/* returns 1->4 if it moved, 0 if it hasn't */
/* check the corresponding key switch:
	== 1: increase speed vector up to max-speed
	== 0: decrerase speed vector down to zero
check the correspondig dir vector:
	!= 0: move of that value,
	== 0: do nothing. */
int	move_player(t_mlx *mlx)
{
	// speed_lx_rx(mlx);
	// speed_up_dw(mlx);
	direction_oriented_movement(mlx);
	// /* ft_ */printf("diff[%f, %f, %f, %f]\n", diff[0], diff[1], diff[2], diff[3]);
	move_and_slide(&mlx->player, mlx->map);
	// other_forces(mlx, diff);
	return (0);
}
