/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:47:19 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/22 22:11:22 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define DIST_MIN 0.01f

int	move_player(t_mlx *mlx);

/* returns the 'legal' value of the 'new_x' based on map limitations */
static float x_cropped(t_mlx *mlx, float old_y, float new_x)
{
	const int	x_max = ft_strlen(mlx->map.mtx[(int)old_y]);

	if (new_x < 0)
		return (DIST_MIN);
	if (new_x > x_max)
		return (x_max - DIST_MIN);
	if (mlx->map.mtx[(int)old_y][(int)new_x] == '1')
	{
		if (new_x - (int)new_x > 0.5f)
			return ((int)new_x + 1.0f + DIST_MIN);
		else
			return((int)new_x - DIST_MIN);
	}
	return (new_x);
}

/* returns the 'legal' value of the 'new_y' based on map limitations */
static float y_cropped(t_mlx *mlx, float old_x, float new_y)
{
	const int	y_max = ft_mtxlen((void **)mlx->map.mtx);

	if (new_y < 0)
		return (DIST_MIN);
	if (new_y > y_max)
		return (y_max - DIST_MIN);
	if (mlx->map.mtx[(int)new_y][(int)old_x] == '1')
	{
		if (new_y - (int)new_y > 0.5f)
			return ((int)new_y + 1.0f + DIST_MIN);
		else
			return((int)new_y - DIST_MIN);
	}
	return (new_y);
}

static int move_lx_rx(t_mlx *mlx, float mspeed)
{
	const float	x_diff = mspeed * DIST_MIN * cosf((mlx->player.dir[0] * M_PI / 180) - M_PI_2);
	const float	y_diff = mspeed * DIST_MIN * sinf((mlx->player.dir[0] * M_PI / 180) - M_PI_2);
	float		new_pos[2];
	int			moved[2];

	ft_memset(moved, 0, 2 * sizeof(int));
	ft_memcpy(new_pos, mlx->player.pos, 2 * sizeof(float));
	// Calculate the new X and Y positions using the player's direction
	if (mlx->key_lx_rx[1] == 1) {
		if (x_diff && ++moved[0])
			new_pos[0] += x_diff;
		if (y_diff && ++moved[1])	
			new_pos[1] += y_diff;
	}
	
	// Move backward (decrease position in direction opposite to the player's facing)
	if (mlx->key_lx_rx[0] == 1) {
		if (x_diff && ++moved[0])
			new_pos[0] -= x_diff;
		if (y_diff && ++moved[1])	
			new_pos[1] -= y_diff;
	}

	// check movement validity
	if (moved[1] != 0)
		mlx->player.pos[1] = y_cropped(mlx, mlx->player.pos[0], new_pos[1]);
	if (moved[0] != 0)
		mlx->player.pos[0] = x_cropped(mlx, mlx->player.pos[1], new_pos[0]);

	// ft_memcpy(mlx->player.pos, new_pos, 2 * sizeof(float));
	return (moved[0] + moved[1]);
}

static int move_up_dw(t_mlx *mlx, float mspeed)
{
	const float	x_diff = mspeed * DIST_MIN * cosf(mlx->player.dir[0] * M_PI / 180);
	const float	y_diff = mspeed * DIST_MIN * sinf(mlx->player.dir[0] * M_PI / 180);
	float		new_pos[2];
	int			moved[2];

	ft_memset(moved, 0, 2 * sizeof(int));
	ft_memcpy(new_pos, mlx->player.pos, 2 * sizeof(float));
	// Calculate the new X and Y positions using the player's direction
	if (mlx->key_up_dw[1] == 1) {
		if (x_diff && ++moved[0])
			new_pos[0] += x_diff;
		if (y_diff && ++moved[1])	
			new_pos[1] += y_diff;
	}
	
	// Move backward (decrease position in direction opposite to the player's facing)
	if (mlx->key_up_dw[0] == 1) {
		if (x_diff && ++moved[0])
			new_pos[0] -= x_diff;
		if (y_diff && ++moved[1])	
			new_pos[1] -= y_diff;
	}

	// check movement validity
	if (moved[1] != 0)
		mlx->player.pos[1] = y_cropped(mlx, mlx->player.pos[0], new_pos[1]);
	if (moved[0] != 0)
		mlx->player.pos[0] = x_cropped(mlx, mlx->player.pos[1], new_pos[0]);

	// ft_memcpy(mlx->player.pos, new_pos, 2 * sizeof(float));
	return (moved[0] + moved[1]);
}

/* Jump feature by Fre007 */
/* returns 1->4 if it moved, 0 if it hasn't */
int	move_player(t_mlx *mlx)
{
	const float mspeed = mlx->player.mspeed;
	int			moved;

	moved = 0;
	if (mlx->key_lx_rx[0] == 1 || mlx->key_lx_rx[1] == 1)
		moved += move_lx_rx(mlx, mspeed);
	if (mlx->key_up_dw[0] == 1 || mlx->key_up_dw[1] == 1)
		moved += move_up_dw(mlx, mspeed);

	if (mlx->jump_key[0] != 0 && mlx->jump_key[1] == 0)	// pressed space
		mlx->jump_key[1] = 1;
	if (mlx->player.pos[2] >= mlx->player.jheigth)
		mlx->jump_key[1] = 2;
	if (mlx->player.pos[2] <= (2/*  + mlx->player.jspeed */) && mlx->jump_key[1] == 2)
		mlx->jump_key[1] = 0;
	
	if (mlx->jump_key[1] == 1)
	{
		mlx->player.pos[2] *= (DIST_MIN * mlx->player.jspeed)/* (mlx->player.pos[2] * 2)- mlx->player.pos[2] */;
	}
	else if (mlx->jump_key[1] == 2)
	{
		mlx->player.pos[2] /= (DIST_MIN * mlx->player.jspeed);
	}
	if (moved)
	{
		// ft_printf("moved player (%f, %f)\n", mlx->player.pos[0], mlx->player.pos[1]);
		return (1);
	}
	return (0);
}
