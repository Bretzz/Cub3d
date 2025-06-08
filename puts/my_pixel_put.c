/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:57:34 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/08 16:49:46 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* takes 'mlx' a pixel coordinates and a color as parameters.
Sets the color of said pixel to the passed color.
NOTE: out of boundaries pixel are handled */
void	my_pixel_put(void *my_struct, int x, int y, unsigned int color)
{
	t_mlx *const	mlx = (t_mlx *)my_struct;
	char			*dst;

	if (my_struct == NULL
		|| mlx->img.addr == NULL)
		return ;
	if (x < 0 || y < 0 || x >= MLX_WIN_X || y >= MLX_WIN_Y)
		return ;
	dst = mlx->img.addr + (y * mlx->img.line_length
			+ x * (mlx->img.bits_per_pixel / sizeof(int *)));
	*(unsigned int *)dst = color;
}
