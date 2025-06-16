/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:53:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/10 15:31:22 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	update_frame(void *arg)
{
	t_mlx *const		mlx = (t_mlx *)arg;
	static unsigned int	frame;

	if (frame++ % mlx->frames == 0)
	{
		move_player(mlx);
		move_mouse(mlx);
		mlx->player.dir[0] = normalize_dir(mlx->player.dir[0]);
		mlx->player.dir[1] = normalize_dir(mlx->player.dir[1]);
		if (!put_board(mlx))
			clean_exit(mlx);
	}
	return (0);
}
