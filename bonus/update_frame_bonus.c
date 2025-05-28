/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:53:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 22:51:56 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include <sys/time.h>

#include <stdio.h>

/* static  */int	get_fps(int frame)
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
	t_mlx *const 		mlx = (t_mlx *)arg;
	char				buffer[MSG_LEN + 6];
	static unsigned int	frame;

	// ft_printf("frames %d\n", mlx->frames);
	if (frame++ % mlx->frames == 0)
	{
		mlx->player.pos = (float *)mlx->lobby[*mlx->index].pos;
		mlx->player.dir = (float *)mlx->lobby[*mlx->index].tar;
		if (move_player(mlx) != 0)
		{
			buffer_player_action(mlx->lobby[*mlx->index], "update", buffer);
			// ft_printf("send_all(%p, %s, %u)\n", mlx, buffer, ft_strlen(buffer));
			send_all(mlx, buffer, ft_strlen(buffer), 0);
		}
		move_mouse(mlx);
		put_board(mlx);
	}
	else
		usleep(1000);
	if (frame % (75) == 0) 
		mlx->fps = get_fps(frame / mlx->frames);
	if (frame % (3000) == 0) 
		print_lobby(lbb_get_ptr(NULL));
	return (0);
}
