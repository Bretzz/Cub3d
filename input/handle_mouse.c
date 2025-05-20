/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:29:54 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 12:20:10 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_mouse(int keysym, int x, int y, t_mlx *mlx)
{
	// char	buffer[92];
	float	ray;

	(void)x; (void)y;
	if (keysym == 1) // keysym == 1
	{
		// const float angle = atan2((mlx->player.pos[1] - y / mlx->map_dim[2]), (mlx->player.pos[0] - x / mlx->map_dim[2]));
		// ft_printf("casting ray from (%f, %f) with angle %f\n", mlx->player.pos[0], mlx->player.pos[1], angle * 180 / M_PI);
		ray = cast_ray(mlx, mlx->player.pos[0], mlx->player.pos[1], mlx->player.dir[0]);
		ft_printf("ray length %f\n", ray);
	}
	// else if (keysym == 3) // keysym == 3
	// {
	// 	mlx->player.tar[0] = x;
	// 	mlx->player.tar[1] = y;
	// 	ft_printf("RAT-RAY!!!\n");
	// 	ft_printf("ray of length %d\n", cast_ray(mlx, mlx->player.pos,
	// 		atan2((mlx->player.pos[1] - mlx->player.tar[1]),
	// 			(mlx->player.pos[0] - mlx->player.tar[0]))));
	// }
	else
		ft_printf("Mouse thing N. %d\n", keysym);
	return (0);
}