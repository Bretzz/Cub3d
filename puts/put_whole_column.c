/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_whole_column.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:38:02 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/10 12:32:29 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "puts.h"

int	put_whole_column(void *my_struct, int x, float len, unsigned int color)
{
	t_mlx *const	mlx = (t_mlx *)my_struct;
	const int		mid_line = MLX_WIN_Y / 2;
	int				heigth;
	int				y;

	if (len < 0)
		heigth = 0;
	else if (len == 0)
		heigth = MLX_WIN_Y / 2;
	else
		heigth = (MLX_WIN_X / 2) / len;
	y = 0;
	while (y < mid_line - heigth)
		my_pixel_put(&mlx->img, x, y++, mlx->map.sky);
	while (y < mid_line + heigth)
	{
		if (y > MLX_WIN_Y)
			break ;
		my_pixel_put(&mlx->img, x, y++, color * (int)mlx->ray.face);
	}
	while (y < MLX_WIN_Y)
		my_pixel_put(&mlx->img, x, y++, mlx->map.floor);
	return (0);
}
