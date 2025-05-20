/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_central_line_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:17:16 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 22:25:44 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_central_line(void *my_struct, int x, float len, unsigned int color)
{
	t_mlx	*const	mlx = (t_mlx *)my_struct;
	const int		mid_line = cos(mlx->player.dir[1] * M_PI / 180) * (2 * mlx->win_y) + (mlx->win_y / 2);
	int				heigth;
	int				y;

	if (len < 0)
		return (1);
	if (len == 0)
		heigth = mlx->win_y / 2;
	else
		heigth = (mlx->win_y) / len;	// dim 0?
	y = 0;
	while (y < heigth)
	{
		my_pixel_put(mlx, x, mid_line + y, color);
		my_pixel_put(mlx, x, mid_line - y, color);
		y++;
	}
	return (0);
}
