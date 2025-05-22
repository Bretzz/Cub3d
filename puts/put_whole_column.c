/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_whole_column.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:38:02 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/22 14:04:41 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_whole_column(void *my_struct, int x, float len, unsigned int color)
{
	t_mlx	*const	mlx = (t_mlx *)my_struct;
	const int		mid_line = mlx->win_y / 2;
	int				heigth;
	int				y;

	if (len < 0)
		heigth = 0;
	else if (len == 0)
		heigth = mlx->win_y / 2;
	else
		heigth = (mlx->win_x / 2) / len;	// dim 0?
	//ft_printf("height %d\n", heigth);
	y = 0;
	while (y < mid_line - heigth)
		my_pixel_put(mlx, x, y++, mlx->map.sky);
	while (y < mid_line + heigth)
	{
		if (y > mlx->win_y)
			break ;
		my_pixel_put(mlx, x, y++, color);
	}
	while (y < mlx->win_y)
		my_pixel_put(mlx, x, y++, mlx->map.floor);
	return (0);
}

