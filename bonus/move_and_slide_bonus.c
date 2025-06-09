/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_slide_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:00:48 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 14:06:37 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

#define DIST_MIN 0.01f
#define DELTA_SPEED 0.001f

/* returns the 'legal' value of the 'new_x' based on map limitations
NOTE: 'old_y' and 'new_x' must be legal values of 'pos' or it
will segfault. */
static float	collide_x(t_map map, float old_y, float new_x)
{
	if (map.mtx[(int)old_y][(int)new_x] == '1')
	{
		if (new_x - (int)new_x > 0.5f)
			return ((int)new_x + 1.0f + DIST_MIN);
		else
			return ((int)new_x - DIST_MIN);
	}
	return (new_x);
}

/* returns the 'legal' value of the 'new_y' based on map limitations
NOTE: 'old_x' and 'new_y' must be legal values of 'pos' or it
will segfault. */
static float	collide_y(t_map map, float old_x, float new_y)
{
	if (map.mtx[(int)new_y][(int)old_x] == '1')
	{
		if (new_y - (int)new_y > 0.5f)
			return ((int)new_y + 1.0f + DIST_MIN);
		else
			return ((int)new_y - DIST_MIN);
	}
	return (new_y);
}

/* modify the x component of the player coordinates */
static int	x_move(t_local *player, t_map map, float x_speed, int x_max)
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
		player->pos[0] = collide_x(map, player->pos[1],
				player->pos[0] + x_speed);
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
		player->pos[1] = collide_y(map, player->pos[0],
				player->pos[1] + y_speed);
	return (0);
}

/* moves the player (.pos) based on the speed (.speed)
NOTE: it's the only place where we change player.pos' values */
int	move_and_slide(t_local *player, t_map map)
{
	const int	x_max = ft_strlen(map.mtx[(int)player->pos[1]]);
	const float	x_speed = player->speed[0] * DELTA_SPEED;
	const float	y_speed = player->speed[1] * DELTA_SPEED;

	x_move(player, map, x_speed, x_max);
	y_move(player, map, y_speed);
	if (player->pos[2] + (DELTA_SPEED * player->speed[2])
		< player->jground)
		player->pos[2] = player->jground;
	else
		player->pos[2] += DELTA_SPEED * player->speed[2];
	return (0);
}
