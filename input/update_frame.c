/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:53:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/26 15:41:19 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	update_frame(void *arg)
{
	t_mlx *const		mlx = (t_mlx *)arg;
	static unsigned int	frame;

	if (frame++ % 11 == 0)
	{
		move_player(mlx);
		move_mouse(mlx);
		mlx->player.dir[0] = normalize_dir(mlx->player.dir[0]);
		mlx->player.dir[1] = normalize_dir(mlx->player.dir[1]);
		if (!put_board(mlx))
			clean_exit(mlx, EXIT_FAILURE);
	}
	else
		usleep(1000);
	if (frame % 10 == 0)
		mlx->fps = get_fps(frame);
	return (0);
}
