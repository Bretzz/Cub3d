/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:29:54 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/22 12:31:21 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_mouse(int keysym, int x, int y, t_mlx *mlx)
{
	float	ray;

	(void)x;
	(void)y;
	if (keysym == 1)
	{
		mlx->player.sprite_x++;
		ray = cast_ray(mlx,
				mlx->player.pos[0],
				mlx->player.pos[1],
				mlx->player.dir[0]);
		mlx->player.sprite_x--;
		ft_printf("ray length %f\n", ray);
	}
	else
		ft_printf("Mouse thing N. %d\n", keysym);
	return (0);
}
