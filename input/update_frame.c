/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:53:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 17:37:40 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	update_frame(void *arg)
{
	t_mlx *const		mlx = (t_mlx *)arg;
	static unsigned int	frame;

	move_player(mlx);
	move_mouse(mlx);
	mlx->player.dir[0] = normalize_dir(mlx->player.dir[0]);
	mlx->player.dir[1] = normalize_dir(mlx->player.dir[1]);
	if (!put_board(mlx))
		clean_exit(mlx, EXIT_FAILURE);
	frame++;
	if (frame % 10 == 0)
		mlx->fps = get_fps(frame);
	return (0);
}
