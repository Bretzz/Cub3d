/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_central_line_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:17:16 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 20:39:28 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_central_line(void *my_struct, int x, float len, unsigned int color)
{
	t_mlx	*const	mlx = (t_mlx *)my_struct;
	const int		mid_line =/*  mlx->player.pos[2] +  */cos(mlx->player.dir[1] * M_PI / 180) * (2 * mlx->win_y) + (mlx->win_y / 2);
	int				heigth;
	int				y;
	char			up_dw[2];

	if (len < 0)
		return (1);
	if (len == 0)
		heigth = mlx->win_y / 2;
	else
		heigth = (mlx->win_x / 2) / len;	// dim 0?
	//ft_printf("height %d\n", heigth);
	ft_memset(up_dw, 1, 2 * sizeof(char));
	y = 0;
	while ((up_dw[0] || up_dw[1]) && y < heigth)
	{
		if (mid_line + y > mlx->win_y)
			up_dw[0] = 0;
		my_pixel_put(mlx, x, mid_line + y, color);
		if (mid_line - y < 0)
			up_dw[1] = 0;
		my_pixel_put(mlx, x, mid_line - y, color);
		y++;
	}
	return (0);
}
