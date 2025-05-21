/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:53:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 17:38:10 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

#include <stdio.h>

int	get_fps(int frame)
{
	static struct timeval	old_time;
	static int				old_frame;
	int						fps;
	struct timeval			now_time;

	if (old_frame == 0)
	{
		gettimeofday(&old_time, NULL);
		old_frame = frame;
		return (0);
	}
	gettimeofday(&now_time, NULL);
	double time = (double)(((now_time.tv_sec * 1000000 + now_time.tv_usec) - (old_time.tv_sec * 1000000 + old_time.tv_usec))) / 1000000;
	fps = (frame - old_frame) / time;
	old_time = now_time;
	old_frame = frame;
	return (fps);
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
	else
		usleep(1000);
	if (frame % (50) == 0)
		mlx->fps = get_fps(frame / mlx->frames);
	return (0);
}
