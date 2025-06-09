/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_whole_column_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:38:02 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 23:11:04 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	put_whole_column(void *my_struct, int x, float len, unsigned int color)
{
	t_mlx	*const	mlx = (t_mlx *)my_struct;
	const int		mid_line = cos(mlx->player.dir[1] * M_PI / 180) * (2 * MLX_WIN_Y) + (MLX_WIN_Y / 2);
	int				heigth;
	int				y;

	if (len < 0)
		heigth = 0;
	else if (len == 0)
		heigth = MLX_WIN_Y;
	else
		heigth = MLX_WIN_X / len;	// dim 0?
	// if (heigth > MLX_WIN_Y)
	int		z = heigth / (mlx->player.pos[2] + 1);	// 0 -> 1 slide, 1 -> 16 jump
	int		cw = z;
	int		tw = heigth - z;
	//ft_printf("height %d\n", heigth);
	(void)color, (void)tw; (void)cw; (void)z; (void)mid_line; (void)x;
	y = 0;
	// ft_printf("sky, ml %d, cw %d\n", mid_line, cw);
	while (y < mid_line - cw && y < MLX_WIN_Y)
		my_pixel_put(mlx, x, y++, mlx->map.sky);
	// ft_printf("mid\n");
	// while (y < mid_line + tw && y < MLX_WIN_Y)
	// {
	// 	if (y > MLX_WIN_Y)
	// 		break ;
	// 	my_pixel_put(mlx, x, y++, color * (int)mlx->ray.face);
	// }
	// ft_printf("floor\n");
	// while (y < MLX_WIN_Y)
	// 	my_pixel_put(mlx, x, y++, mlx->map.floor);
	return (0);
}

