/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:47:19 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 22:30:13 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define DIST_MIN 0.01f
#define DELTA_SPEED 0.001f

int	move_player(t_mlx *mlx);

/* modify the x component of the player coordinates */
static int	x_move(t_local *player, float x_speed, int x_max)
{
	if (player->pos[0] + x_speed >= x_max)
	{
		player->pos[0] = x_max - DIST_MIN;
		player->speed[0] = 0;
	}
	else if (player->pos[0] + x_speed <= 0)
	{
		player->pos[0] = 0 + DIST_MIN;
		player->speed[0] = 0;
	}
	else
		player->pos[0] += x_speed;
	return (0);
}

/* modify the y component of the player coordinates */
static int	y_move(t_local *player, t_map map, float y_speed)
{
	if (player->pos[1] + y_speed >= map.stats[1])
	{
		player->pos[1] = map.stats[1] - DIST_MIN;
		player->speed[1] = 0;
	}
	else if (player->pos[1] + y_speed <= 0)
	{
		player->pos[1] = 0 + DIST_MIN;
		player->speed[1] = 0;
	}
	else
		player->pos[1] += y_speed;
	return (0);
}

/* moves the player (.pos) based on the speed (.speed)
NOTE: it's the only place where we change player.pos' values */
static int	move_and_slide(t_local *player, t_map map)
{
	const int	x_max = map.stats[0];
	const float	x_speed = player->speed[0] * DELTA_SPEED;
	const float	y_speed = player->speed[1] * DELTA_SPEED;

	x_move(player, x_speed, x_max);
	y_move(player, map, y_speed);
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
	direction_oriented_movement(mlx);
	move_and_slide(&mlx->player, mlx->map);
	return (0);
}
