/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_central_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:16:27 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 17:35:40 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_central_line(void *my_struct, int x, float len, unsigned int color)
{
	t_mlx	*const	mlx = (t_mlx *)my_struct;
	int				heigth;
	int				y;
	char			up_dw[2];

	if (len < 0)
		return (1);
	if (len == 0)
		heigth = mlx->win_y / 2;
	else
		heigth = (mlx->win_x / 2) / len;	// dim 0?
	if (heigth > mlx->win_y / 2)
		heigth = mlx->win_y / 2;
	ft_memset(up_dw, 1, 2 * sizeof(char));
	y = 0;
	while ((up_dw[0] || up_dw[1]) && y < heigth)
	{
		if ((mlx->win_y / 2) + y > mlx->win_y)
			up_dw[0] = 0;
		my_pixel_put(mlx, x, (mlx->win_y / 2) + y, color);
		if ((mlx->win_y / 2) - y < 0)
			up_dw[1] = 0;
		my_pixel_put(mlx, x, (mlx->win_y / 2) - y, color);
		y++;
	}
	return (0);
}
