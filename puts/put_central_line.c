/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_central_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:16:27 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 11:49:50 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_central_line(void *my_struct, int x, float len, unsigned int color)
{
	t_mlx	*const	mlx = (t_mlx *)my_struct;
	int				heigth;
	int				y;

	if (len < 0)
		return (1);
	if (len == 0)
		heigth = mlx->win_y / 2;
	else
		heigth = (mlx->win_y) / len;	// dim 0?
	if (heigth > mlx->win_y / 2)
		heigth = mlx->win_y / 2;
	y = 0;
	while (y < heigth)
	{
		my_pixel_put(mlx, x, /* sin(dir) * (mlx->win_y) +  */(mlx->win_y / 2) + y, color);
		my_pixel_put(mlx, x, /* sin(dir) * (mlx->win_y) +  */(mlx->win_y / 2) - y, color);
		y++;
	}
	return (0);
}
