/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_whole_column_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:38:02 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 16:33:37 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	put_whole_column(void *my_struct, int x, float len, unsigned int color)
{
	t_mlx	*const	mlx = (t_mlx *)my_struct;
	const int		mid_line = cos(mlx->player.dir[1] * M_PI / 180) * (2 * MLX_WIN_Y) + (MLX_WIN_Y / 2);
	int				heigth;
	int				y;

	if (x < 0 || x >= MLX_WIN_X)
		return (1);
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
	// ft_printf("sky, ml %d, cw %d\n", mid_line, cw);
	
	unsigned int	put_color;
	y = 0;
	while (y < MLX_WIN_Y)
	{
		if (y < mid_line - cw)
			put_color = mlx->map.sky;
		else if (y < mid_line + tw)
			put_color = color * (int)mlx->ray.face;
		else
			put_color = mlx->map.floor;
		*(unsigned int *)(mlx->img->addr + (y * mlx->img->line_length)
			+ (x * mlx->img->bpp)) = put_color;
		y++;
	}
	return (0);
}
