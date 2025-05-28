/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:47:19 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/29 00:14:05 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

#define DIST_MIN 0.01f
#define	DELTA_SPEED 0.001f

int	move_player(t_mlx *mlx);

/* returns the 'legal' value of the 'new_x' based on map limitations
NOTE: 'old_y' and 'new_x' must be legal values of 'pos' or it
will segfault. */
static float collide_x(t_map map, float old_y, float new_x)
{
	if (map.mtx[(int)old_y][(int)new_x] == '1')
	{
		if (new_x - (int)new_x > 0.5f)
			return ((int)new_x + 1.0f + DIST_MIN);
		else
			return((int)new_x - DIST_MIN);
	}
	return (new_x);
}

/* returns the 'legal' value of the 'new_y' based on map limitations
NOTE: 'old_x' and 'new_y' must be legal values of 'pos' or it
will segfault. */
static float collide_y(t_map map, float old_x, float new_y)
{
	if (map.mtx[(int)new_y][(int)old_x] == '1')
	{
		if (new_y - (int)new_y > 0.5f)
			return ((int)new_y + 1.0f + DIST_MIN);
		else
			return((int)new_y - DIST_MIN);
	}
	return (new_y);
}

/* changes the speed[3] component based on key_jump_slide */
int	jump_and_crouch(t_mlx *mlx)
{
	static int	jumped;
	static int	shield;

	if (!shield && mlx->keys.jump_slide[1])
	{
		mlx->player.tspeed[0] /= 2;						// reducing speed (stacks with shift)
		mlx->player.jground = 0.4f;						// lowering ground level (do not go below 0)
		mlx->player.pos[2] -= 1 - mlx->player.jground;	// lowering player to match the level
		shield = 1;
		return (1);
	}
	else if (shield && !mlx->keys.jump_slide[1])
	{
		mlx->player.tspeed[0] *= 2;
		mlx->player.jground = 1;
		mlx->player.pos[2] += 1 - mlx->player.jground;
		shield = 0;
		return (1);
	}
	// printf("jumped %d, jspeed %d, pos %f\n", jumped, mlx->player.speed[2], mlx->player.pos[2]);
	if (jumped == 0 && mlx->keys.jump_slide[0] == 1)
	{
		mlx->player.speed[2] = mlx->player.tspeed[1];
		jumped = 1;
		return (0);
	}
	if (jumped == 1)
	{
		if (mlx->player.pos[2] == mlx->player.jground)	// ground == 1
		{
			mlx->player.speed[2] = 0;
			jumped = 0;
			return (0);
		}
		mlx->player.speed[2] -= (mlx->player.tspeed[1] / 17);
	}
	// if ((shield && mlx->keys.jump_slide[1])
	// 	|| (!shield && !mlx->keys.jump_slide[1]))
	// 	return (1);
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
		player->pos[0] = collide_x(map, player->pos[1], player->pos[0] + x_speed);

	// y-limits [0, map-size]
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
		player->pos[1] = collide_y(map, player->pos[0], player->pos[1] + y_speed);

	// z movement
	if (player->pos[2] + (DELTA_SPEED * player->speed[2]) < player->jground)	// ground == 1
		player->pos[2] = player->jground;
	else
		player->pos[2] += DELTA_SPEED * player->speed[2];
	return (0);
}

/* changes tspeed[0] if we are shifting */
static void	shift_tspeed(t_mlx *mlx)
{
	static int shield;

	if (!shield && mlx->keys.shift)
	{
		mlx->player.tspeed[0] /= 2;
		shield = 1;
	}
	else if (shield && !mlx->keys.shift)
	{
		mlx->player.tspeed[0] *= 2;
		shield = 0;
	}
}

/* Jump feature by Fre007 */
/* returns 1->4 if it moved, 0 if it hasn't */
/* check the corresponding key switch:
	== 1: increase speed vector up to max-speed
	== 0: decrerase speed vector down to zero
check the correspondig dir vector:
	!= 0: move of that value,
	== 0: do nothing. */
int	move_player(t_mlx *mlx)
{
	int	crouch = 0;

	shift_tspeed(mlx);
	direction_oriented_movement(mlx);
	crouch = jump_and_crouch(mlx);
	// ft_printf("crouch %d\n", crouch);
	// /* ft_ */printf("diff[%f, %f, %f, %f]\n", diff[0], diff[1], diff[2], diff[3]);
	move_and_slide(&mlx->player, mlx->map);
	// other_forces(mlx, diff);
	if (mlx->player.speed[0]
		|| mlx->player.speed[1]
		|| mlx->player.speed[2]
		|| crouch)
		return (1);
	return (0);
}

