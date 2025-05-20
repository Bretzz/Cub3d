/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:53:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 12:16:03 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define DIST_MIN 0.01f

/* returns the 'legal' value of the 'new_x' based on map limitations */
static float x_cropped(t_mlx *mlx, float old_y, float new_x)
{
	const int	x_max = ft_strlen(mlx->map[(int)old_y]);
	// const int	y_max = ft_mtxlen((void **)mlx->map);

	if (new_x < 0)
		return (0);
	if (new_x > x_max)
		return (x_max);
	if (mlx->map[(int)old_y][(int)new_x] == '1')
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
	// const int	x_max = ft_strlen(mlx->map[(int)old_y]);
	const int	y_max = ft_mtxlen((void **)mlx->map);

	if (new_y < 0)
		return (0);
	if (new_y > y_max)
		return (y_max);
	if (mlx->map[(int)new_y][(int)old_x] == '1')
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
	const float	x_diff = mspeed * cosf((mlx->player.dir[0] * M_PI / 180) - M_PI_2);
	const float	y_diff = mspeed * sinf((mlx->player.dir[0] * M_PI / 180) - M_PI_2);
	float		new_pos[2];
	int			moved[2];
	
	ft_memset(moved, 0, 2 * sizeof(int));
	ft_memcpy(new_pos, mlx->player.pos, 2 * sizeof(float));
	if (mlx->key_lx_rx[1] == 1) {
		// Calculate the new X and Y positions using the player's direction
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
	if (moved[0] != 0)
		mlx->player.pos[0] = x_cropped(mlx, mlx->player.pos[1], new_pos[0]);
	if (moved[1] != 0)
		mlx->player.pos[1] = y_cropped(mlx, mlx->player.pos[0], new_pos[1]);

	// ft_memcpy(mlx->player.pos, new_pos, 2 * sizeof(float));
	return (moved[0] + moved[1]);
}

static int move_up_dw(t_mlx *mlx, float mspeed)
{
	const float	x_diff = mspeed * cosf(mlx->player.dir[0] * M_PI / 180);
	const float	y_diff = mspeed * sinf(mlx->player.dir[0] * M_PI / 180);
	float		new_pos[2];
	int			moved[2];
	
	ft_memset(moved, 0, 2 * sizeof(int));
	ft_memcpy(new_pos, mlx->player.pos, 2 * sizeof(float));
	if (mlx->key_up_dw[1] == 1) {
		// Calculate the new X and Y positions using the player's direction
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
	if (moved[0] != 0)
		mlx->player.pos[0] = x_cropped(mlx, mlx->player.pos[1], new_pos[0]);
	if (moved[1] != 0)
		mlx->player.pos[1] = y_cropped(mlx, mlx->player.pos[0], new_pos[1]);

	// ft_memcpy(mlx->player.pos, new_pos, 2 * sizeof(float));
	return (moved[0] + moved[1]);
}

/* returns 1->4 if it moved, 0 if it hasn't */
static int	move_player(t_mlx *mlx)
{
	const float mspeed = mlx->player.mspeed;
	int			moved;

	moved = 0;
	moved += move_lx_rx(mlx, mspeed);
	moved += move_up_dw(mlx, mspeed);

	if (moved)
	{
		// ft_printf("moved player (%f, %f)\n", mlx->player.pos[0], mlx->player.pos[1]);
		return (1);
	}
	return (0);
}

static int	move_mouse(t_mlx *mlx)
{
	const float	delta_dir = (float)mlx->player.fov[0] / mlx->win_x;

	if (mlx->on_window == 0)
		return (1);
	mlx_mouse_get_pos(mlx->mlx, mlx->win, &mlx->mouse[0], &mlx->mouse[1]);
	if (mlx->mouse[0] != mlx->win_x / 2)
	{
		mlx->player.dir[0] += (mlx->mouse[0] - (mlx->win_x / 2)) * delta_dir;
		// mlx->player.dir[0] = mlx->player.dir[0] % 360;
		// if (mlx->player.dir[0] < -M_PI)
		// 	mlx->player.dir[0] = M_PI - (-mlx->player.dir[0] - M_PI);
		// else if (mlx->player.dir[0] > M_PI)
		// 	mlx->player.dir[0] = -M_PI + (mlx->player.dir[0] - M_PI);
		// mlx->player.dir[0] = normalize_angle(mlx->player.dir[0]);
		// printf("dir0: %f\n", mlx->player.dir[0]);
	}
	if (mlx->mouse[1] != mlx->win_y / 2)
	{
		mlx->player.dir[1] += ((mlx->win_y / 2) - mlx->mouse[1]) / 2;
		// mlx->player.dir[1] = mlx->player.dir[1] % 360;
		// if (mlx->player.dir[0] < -M_PI)
		// 	mlx->player.dir[0] = M_PI - (-mlx->player.dir[0] - M_PI);
		// else if (mlx->player.dir[0] > M_PI)
		// 	mlx->player.dir[0] = -M_PI + (mlx->player.dir[0] - M_PI);
		// printf("dir1: %f\n", mlx->player.dir[1]);
	}
	mlx_mouse_move(mlx->mlx, mlx->win, mlx->win_x / 2, mlx->win_y / 2);
	return (0);
}

int update_frame(void *arg)
{
	t_mlx *const mlx = (t_mlx *)arg;
	static unsigned int	frame;

	if (frame++ % mlx->frames == 0)
	{
		move_player(mlx);
		move_mouse(mlx);
		put_board(mlx);
	}
	usleep(1000);
	return (0);
}
