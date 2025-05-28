/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mouse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:57:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/29 00:09:28 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	move_mouse(t_mlx *mlx);

int	move_mouse(t_mlx *mlx)
{
	const float	delta_dir = (float)mlx->player.fov[0] / mlx->win_x;
	float		y_diff;
	char		moved[2];

	if (mlx->on_window == 0)
		return (0);
	ft_memset(moved, 0, 2 * sizeof(char));
	mlx_mouse_get_pos(mlx->mlx, mlx->win, &mlx->keys.mouse[0], &mlx->keys.mouse[1]);	// macOS issues
	if (mlx->keys.mouse[0] != mlx->win_x / 2)
	{
		mlx->player.dir[0] += (mlx->keys.mouse[0] - (mlx->win_x / 2)) * delta_dir;
		moved[0] = 1;
	}
	if (mlx->keys.mouse[1] != mlx->win_y / 2)
	{
		y_diff = (float)(mlx->keys.mouse[1] - (mlx->win_y / 2)) / 6;		// adjust sens
		if ((y_diff > 0 && mlx->player.dir[1] + y_diff <= 180)
			|| (y_diff < 0 && mlx->player.dir[1] + y_diff >= 0))
			mlx->player.dir[1] += y_diff;
		moved[1] = 1;
		// ft_printf("got dir[%f, %f] %f\n", mlx->player.dir[0], mlx->player.dir[1]);
	}
	mlx_mouse_move(mlx->mlx, mlx->win, mlx->win_x / 2, mlx->win_y / 2);	// macOS issues
	if (moved[0] || moved[1])
		return (1);
	return (0);
}
