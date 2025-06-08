/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:29:54 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/08 17:47:22 by topiana-         ###   ########.fr       */
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
		ray = cast_ray(mlx,
				mlx->player.pos[0],
				mlx->player.pos[1],
				mlx->player.dir[0]);
	}
	else
		ft_printf("Mouse thing N. %d\n", keysym);
	return (0);
}
