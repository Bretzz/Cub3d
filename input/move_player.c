/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:47:19 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/26 12:42:05 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DIST_MIN 0.01f
#define	SPEED_DELTA 0.05f

int	move_player(t_mlx *mlx);

/* return the 'legal' value of speed */
float	speed_bound(t_mlx *mlx, float speed)
{
	if (speed > 0 && speed > mlx->player.tspeed[0])
		return (mlx->player.tspeed[0]);
	if (speed < 0 && speed < -mlx->player.tspeed[0])
		return (-mlx->player.tspeed[0]);
	return (speed);
}

/* moves 'speed' towords 0 of 'diff' increments */
static float crunch_speed_diff(float speed, float diff, float friction)
{
	float	new_speed;

	if (speed == 0)
		return (0);
	diff = fabsf(diff) * friction;
	new_speed = speed;
	if (speed > 0)
		new_speed -= diff;
	else
		new_speed += diff;
	if (speed > 0 && new_speed < 0)
		return (0);
	if (speed < 0 && new_speed > 0)
		return (0);
	return (new_speed);
}

/* changes the speed[3] vector based of the keys
pressed:
	A: increses based on angle
	D: increses based on angle
	-: decreses based on angle */
static int	speed_lx_rx(t_mlx *mlx)
{
	const float	x_diff = SPEED_DELTA * cosf((mlx->player.dir[0] * M_PI / 180) - M_PI_2);
	const float	y_diff = SPEED_DELTA * sinf((mlx->player.dir[0] * M_PI / 180) - M_PI_2);

	if (mlx->key_lx_rx[0] == 1)
	{
		mlx->player.speed[0] -= x_diff;
		mlx->player.speed[1] -= y_diff;
	}
	if (mlx->key_lx_rx[1] == 1)
	{
		mlx->player.speed[0] += x_diff;
		mlx->player.speed[1] += y_diff;
	}
	if (mlx->key_lx_rx[0] == 0 && mlx->key_lx_rx[1] == 0)
	{
		mlx->player.speed[0] = crunch_speed_diff(mlx->player.speed[0], x_diff, mlx->player.friction);
		mlx->player.speed[1] = crunch_speed_diff(mlx->player.speed[1], y_diff, mlx->player.friction);
	}

	mlx->player.speed[0] = speed_bound(mlx, mlx->player.speed[0]);
	mlx->player.speed[1] = speed_bound(mlx, mlx->player.speed[1]);

	// ft_printf("lx_rx new vector: (%f, %f, %f)\n", mlx->player.speed[0],  mlx->player.speed[1], mlx->player.speed[2]);
	return (0);
}

/* changes the speed[3] vector based of the keys
pressed:
	A: increses based on angle
	D: increses based on angle
	-: decreses based on angle */
static int	speed_up_dw(t_mlx *mlx)
{
	const float	x_diff = SPEED_DELTA * cosf(mlx->player.dir[0] * M_PI / 180);
	const float	y_diff = SPEED_DELTA * sinf(mlx->player.dir[0] * M_PI / 180);

	if (mlx->key_up_dw[0] == 1)
	{
		mlx->player.speed[0] -= x_diff;
		mlx->player.speed[1] -= y_diff;
	}
	if (mlx->key_up_dw[1] == 1)
	{
		mlx->player.speed[0] += x_diff;
		mlx->player.speed[1] += y_diff;
	}
	if (mlx->key_up_dw[0] == 0 && mlx->key_up_dw[1] == 0)
	{
		mlx->player.speed[0] = crunch_speed_diff(mlx->player.speed[0], x_diff, mlx->player.friction);
		mlx->player.speed[1] = crunch_speed_diff(mlx->player.speed[1], y_diff, mlx->player.friction);
	}

	mlx->player.speed[0] = speed_bound(mlx, mlx->player.speed[0]);
	mlx->player.speed[1] = speed_bound(mlx, mlx->player.speed[1]);

	// ft_printf("up_dw new vector: (%f, %f, %f)\n", mlx->player.speed[0],  mlx->player.speed[1], mlx->player.speed[2]);
	return (0);
}

/* moves the player (.pos) based on the speed (.speed) */
int	move_and_slide(t_local *player, t_map map)
{
	const int	x_max = ft_strlen(map.mtx[(int)player->pos[1]]);

	// x-limits [0, map-size]
	if (player->pos[0] + player->speed[0] > x_max)
	{
		player->pos[0] = x_max - DIST_MIN;
		player->speed[0] = 0;
	}
	else if (player->pos[0] + player->speed[0] < 0)
	{
		player->pos[0] = 0 + DIST_MIN;
		player->speed[0] = 0;
	}
	else
		player->pos[0] += player->speed[0];

	// y-limits [0, map-size]
	if (player->pos[1] + player->speed[1] > map.stats[1])
	{
		player->pos[1] = map.stats[1] - DIST_MIN;
		player->speed[1] = 0;
	}
	else if (player->pos[1] + player->speed[1] < 0)
	{
		player->pos[1] = 0 + DIST_MIN;
		player->speed[1] = 0;
	}
	else
		player->pos[1] += player->speed[1];
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
	speed_lx_rx(mlx);
	speed_up_dw(mlx);
	// /* ft_ */printf("diff[%f, %f, %f, %f]\n", diff[0], diff[1], diff[2], diff[3]);
	move_and_slide(&mlx->player, mlx->map);
	// other_forces(mlx, diff);
	return (0);
}
