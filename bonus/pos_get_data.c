/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:33:53 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/11 16:33:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	pos_get_data(t_mlx *mlx, float *pos, int index);

static void	set_struct_data(t_mlx *mlx,
	t_plot *pos_data, float my_dist, float player_dir)
{
	const int	mid_line = cos(mlx->player.dir[1] * M_PI / 180)
		* (2 * MLX_WIN_Y) + (MLX_WIN_Y / 2);
	const int	x_screen = (MLX_WIN_X / 2) + dir_diff(player_dir,
			mlx->player.dir[0]) * (MLX_WIN_X / mlx->player.fov[0]);
	const int	floor = (MLX_WIN_X / my_dist) - ((MLX_WIN_X / my_dist)
			/ ((mlx->player.pos[2] / (pos_data->pos[2] + 1)) + 1));

	pos_data->seen = 1;
	pos_data->x_screen = x_screen;
	pos_data->y_screen = mid_line + floor;
	pos_data->dist = my_dist;
	pos_data->dir = player_dir;
}

/* fills the t_plot struct with the position data */
int	pos_get_data(t_mlx *mlx, float *pos, int index)
{
	const float	*my_pos = mlx->player.pos;
	const float	dir = atan2((my_pos[1] - pos[1]),
			(my_pos[0] - pos[0])) * 180 / M_PI;
	const float	my_dist = sqrt((pos[0] - my_pos[0]) * (pos[0] - my_pos[0])
			+ (pos[1] - my_pos[1]) * (pos[1] - my_pos[1]));

	ft_memset(&mlx->pos_data[index], 0, sizeof(t_plot));
	ft_memcpy(mlx->pos_data[index].pos, pos, 3 * sizeof(float));
	mlx->pos_data[index].dist = my_dist;
	mlx->pos_data[index].dir = dir;
	if (fabsf(dir_diff(dir, mlx->player.dir[0]))
		> mlx->player.fov[0] / 2)
		return (1);
	cast_ray(mlx, my_pos[0], my_pos[1], dir);
	if (mlx->ray.len > 0 && mlx->ray.len < my_dist)
		return (1);
	set_struct_data(mlx, &mlx->pos_data[index], my_dist, dir);
	return (0);
}
