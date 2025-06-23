/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mouse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:57:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/23 11:37:17 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	move_mouse(t_mlx *mlx);

int	move_mouse(t_mlx *mlx)
{
	const float	delta_x = (float)mlx->player.fov[0] / MLX_WIN_X;
	const float	delta_y = (float)mlx->player.fov[1] / MLX_WIN_Y;
	float		y_diff;
	char		moved[2];

	if (mlx->on_window == 0)
		return (0);
	ft_memset(moved, 0, 2 * sizeof(char));
	mlx_mouse_get_pos(mlx->mlx, mlx->win,
		&mlx->keys.mouse[0], &mlx->keys.mouse[1]);
	if (mlx->keys.mouse[0] != MLX_WIN_X / 2 && ++moved[0])
		mlx->player.dir[0] += (mlx->keys.mouse[0] - (MLX_WIN_X / 2)) * delta_x;
	if (mlx->keys.mouse[1] != MLX_WIN_Y / 2 && ++moved[1])
	{
		y_diff = (float)(mlx->keys.mouse[1] - (MLX_WIN_Y / 2)) * delta_y;
		if ((y_diff > 0 && mlx->player.dir[1] + y_diff <= 180)
			|| (y_diff < 0 && mlx->player.dir[1] + y_diff >= 0))
			mlx->player.dir[1] += y_diff;
	}
	mlx_mouse_move(mlx->mlx, mlx->win, MLX_WIN_X / 2, MLX_WIN_Y / 2);
	if (moved[0] || moved[1])
		return (1);
	return (0);
}
