/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:47:19 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 14:11:09 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	move_player(t_mlx *mlx);

/* updates ground pos and jspeed */
// reducing speed (stacks with shift)
// lowering ground level (do not go below 0)
// lowering player to match the level
static int	update_ground(t_mlx *mlx, int *shield)
{
	if (*shield == 0 && mlx->keys.jump_slide[1])
	{
		mlx->player.tspeed[0] /= 2;
		mlx->player.jground = 0.4f;
		mlx->player.pos[2] -= 1 - mlx->player.jground;
		*shield = 1;
		return (1);
	}
	else if (*shield != 0 && !mlx->keys.jump_slide[1])
	{
		mlx->player.tspeed[0] *= 2;
		mlx->player.jground = 1;
		mlx->player.pos[2] += 1 - mlx->player.jground;
		*shield = 0;
		return (1);
	}
	return (0);
}

/* changes the speed[3] component based on key_jump_slide */
int	jump_and_crouch(t_mlx *mlx)
{
	static int	jumped;
	static int	shield;

	if (update_ground(mlx, &shield) != 0)
		return (1);
	if (jumped == 0 && mlx->keys.jump_slide[0] == 1)
	{
		mlx->player.speed[2] = mlx->player.tspeed[1];
		jumped = 1;
		return (0);
	}
	if (jumped == 1)
	{
		if (mlx->player.pos[2] == mlx->player.jground)
		{
			mlx->player.speed[2] = 0;
			jumped = 0;
			return (0);
		}
		mlx->player.speed[2] -= (mlx->player.tspeed[1] / 17);
	}
	return (0);
}

/* changes tspeed[0] if we are shifting */
static void	shift_tspeed(t_mlx *mlx)
{
	static int	shield;

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
	int	crouch;

	shift_tspeed(mlx);
	direction_oriented_movement(mlx);
	crouch = jump_and_crouch(mlx);
	move_and_slide(&mlx->player, mlx->map);
	if (mlx->player.speed[0]
		|| mlx->player.speed[1]
		|| mlx->player.speed[2]
		|| crouch)
		return (1);
	return (0);
}
