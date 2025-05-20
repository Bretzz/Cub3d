/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:53:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 14:58:17 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
