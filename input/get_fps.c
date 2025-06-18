/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:03:01 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 13:37:30 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <sys/time.h>

int	get_fps(int frame);

// #include <stdio.h>
// #include <time.h>

// int get_fps(int frame) {
//     static int frame_count = 0;
//     static double last_time = 0.0;

//     frame_count++;
// 	(void)frame;
//     double current_time = (double)clock() / CLOCKS_PER_SEC;
//     // Print FPS every second
//     if (current_time - last_time >= 1.0) {
//         ft_printf("FPS: %d\n", frame_count);
//         frame_count = 0;
//         last_time = current_time;
//     }
// 	return (0);
// }

int	get_fps(int frame)
{
	static struct timeval	old_time;
	static int				old_frame;
	int						fps;
	struct timeval			now_time;
	double					delta_time;

	if (old_frame == 0)
	{
		gettimeofday(&old_time, NULL);
		old_frame = frame;
		return (0);
	}
	gettimeofday(&now_time, NULL);
	delta_time = (double)(((now_time.tv_sec * 1000000 + now_time.tv_usec)
				- (old_time.tv_sec * 1000000 + old_time.tv_usec))) / 1000000;
	fps = (frame - old_frame) / delta_time;
	old_time = now_time;
	old_frame = frame;
	return (fps);
}
