/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:57:34 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 02:49:35 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "puts.h"

/* takes 'mlx' a pixel coordinates and a color as parameters.
Sets the color of said pixel to the passed color.
NOTE: out of boundaries pixel are handled */
void	my_pixel_put(void *my_struct, int x, int y, unsigned int color)
{
	t_my_img *const	img = (t_my_img *)my_struct;

	if (my_struct == NULL
		|| img->data == NULL)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->heigth)
		return ;
	*(unsigned int *)(img->data + (y * img->line_length
			+ x * (img->bits_per_pixel / sizeof(int *)))) = color;
}
