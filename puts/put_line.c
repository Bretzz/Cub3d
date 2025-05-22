/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:22:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/22 12:18:56 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_sx(int *p1, int *p2)
{
	int	sx;

	if (p1[0] < p2[0])
		sx = 1;
	else
		sx = -1;
	return (sx);
}

static int	set_sy(int *p1, int *p2)
{
	int	sy;

	if (p1[1] < p2[1])
		sy = 1;
	else
		sy = -1;
	return (sy);
}

/* Basic implementation of the Breshaim line algorithm */
/* p1 are the coords of the first pixel, p2 are the coords of the second one */
int	put_line(t_mlx *mlx, int *p1, int *p2, unsigned int color)
{
	const int	dx_sx[2] = {abs (p2[0] - p1[0]), set_sx(p1, p2)};
	const int	dy_sy[2] = {-abs (p2[1] - p1[1]), set_sy(p1, p2)};
	int			err;
	int			e2;
	int			proj[2];

	ft_memcpy(proj, p1, 2 * sizeof(int));
	err = dx_sx[0] + dy_sy[0];
	while (proj[0] != p2[0] || proj[1] != p2[1])
	{
		e2 = 2 * err;
		if (e2 >= dy_sy[0])
		{
			err += dy_sy[0];
			proj[0] += dx_sx[1];
		}
		if (e2 <= dx_sx[0])
		{
			err += dx_sx[0];
			proj[1] += dy_sy[1];
		}
		my_pixel_put(mlx, proj[0], proj[1], color);
	}
	return (1);
}
