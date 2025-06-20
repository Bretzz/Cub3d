/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_whole_column.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:38:02 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/20 14:58:01 by scarlucc         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"
#include "puts.h"

/* segfaults if len == 0 */
int	put_whole_column(void *my_struct, int x, float len, unsigned int color)
{
	t_mlx *const	mlx = (t_mlx *)my_struct;
	const int		mid_line = MLX_WIN_Y / 2;
	unsigned int	put_color;
	int				heigth;
	int				y;

	if (x < 0 || x >= MLX_WIN_X)
		return (1);
	if (len < 0)
		heigth = 0;
	else if (len == 0)
		heigth = MLX_WIN_Y / 2;
	else
		heigth = (MLX_WIN_X / 2) / len;
	y = 0;
	while (y < MLX_WIN_Y)
	{
		if (y < mid_line - heigth)
			put_color = mlx->map.sky;
		else if (y < mid_line + heigth)
			put_color = color * (int)mlx->ray.face;//colore da sostituire con sprite
		else
			put_color = mlx->map.floor;
		*(unsigned int *)(mlx->img->addr + (y * mlx->img->line_length)
				+ (x * mlx->img->bpp)) = put_color;
		y++;
	}
	return (0);
}
