/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:29:54 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 02:12:10 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_mouse(int keysym, int x, int y, t_mlx *mlx)
{
	float	ray;

	(void)x;
	(void)y;
	if (keysym == 1)
	{
		mlx->player.dir[2]++;
		ray = cast_ray(mlx,
				mlx->player.pos[0],
				mlx->player.pos[1],
				mlx->player.dir[0]);
		mlx->player.dir[2]--;
		if (DEBUG)
			ft_printf("HIT [%f,%f] len %f\n", mlx->ray.hit[0], mlx->ray.hit[1], ray);
	}
	else if (DEBUG)
		ft_printf("Mouse thing N. %d\n", keysym);
	return (0);
}
