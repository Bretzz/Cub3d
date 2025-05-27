/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mouse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:57:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/27 23:55:19 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	move_mouse(t_mlx *mlx);

int	move_mouse(t_mlx *mlx)
{
	const float	delta_dir = (float)mlx->player.fov[0] / mlx->win_x;
	float		y_diff;

	if (mlx->on_window == 0)
		return (1);
	mlx_mouse_get_pos(mlx->mlx, mlx->win, &mlx->keys.mouse[0], &mlx->keys.mouse[1]);	// macOS issues
	if (mlx->keys.mouse[0] != mlx->win_x / 2)
	{
		mlx->player.dir[0] += (mlx->keys.mouse[0] - (mlx->win_x / 2)) * delta_dir;
	}
	if (mlx->keys.mouse[1] != mlx->win_y / 2)
	{
		y_diff = (float)(mlx->keys.mouse[1] - (mlx->win_y / 2)) / 6;		// adjust sens
		if ((y_diff > 0 && mlx->player.dir[1] + y_diff <= 180)
			|| (y_diff < 0 && mlx->player.dir[1] + y_diff >= 0))
			mlx->player.dir[1] += y_diff;
		ft_printf("got dir[%f, %f] %f\n", mlx->player.dir[0], mlx->player.dir[1]);
	}
	mlx_mouse_move(mlx->mlx, mlx->win, mlx->win_x / 2, mlx->win_y / 2);	// macOS issues
	return (0);
}
