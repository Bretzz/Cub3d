/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:53:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/19 22:07:16 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* returns 1->4 if it moved, 0 if it hasn't */
static int	move_player(t_mlx *mlx)
{
	const float mspeed = mlx->player.mspeed;
	int			moved;

	moved = 0;
	if (mlx->key_lx_rx[0] == 1 && ++moved)
		mlx->player.pos[0] -= mspeed;
	if (mlx->key_lx_rx[1] == 1 && ++moved)
		mlx->player.pos[0] += mspeed;
	if (mlx->key_up_dw[0] == 1 && ++moved)
		mlx->player.pos[1] -= mspeed;
	if (mlx->key_up_dw[1] == 1 && ++moved)
		mlx->player.pos[1] += mspeed;
	return (moved);
}

int update_frame(void *arg)
{
	t_mlx *const mlx = (t_mlx *)arg;
	static unsigned int	frame;

	if (frame++ % mlx->frames == 0)
	{
		move_player(mlx);
		put_board(mlx);
	}
	usleep(1000);
	return (0);
}