/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:22:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 21:24:03 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* p1 are the coords of the first pixel, p2 are the coords of the second one */
int	put_line(t_mlx *mlx, int *p1, int *p2, unsigned int color)
{
	int	proj[2];
	int dx =  abs (p2[0] - p1[0]), sx = p1[0] < p2[0] ? 1 : -1;
	int dy = -abs (p2[1] - p1[1]), sy = p1[1] < p2[1] ? 1 : -1; 
	int err = dx + dy, e2; /* error value e_xy */
	ft_memcpy(proj, p1, 2 * sizeof(int));

	for (;;){  /* loop */

		if (proj[0] == p2[0] && proj[1] == p2[1]) break;

		e2 = 2 * err;
		if (e2 >= dy) { err += dy; proj[0] += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; proj[1] += sy; } /* e_xy+e_y < 0 */
		
		my_pixel_put(mlx, proj[0], proj[1], color);

		//my stuff (death check)
		// if (i > 5 && abs(proj[0] - my_pos[0]) < 5 && abs(proj[1] - my_pos[1]) < 5) return (0);

		//if (proj[0] == p2[0] && proj[1] == p2[1]) break;
		// ft_printf("i %d of (%d,%d) -> (%d, %d)\n", i, p1[0], p1[1], p2[0], p2[1]);
	}
	return (1);
}
