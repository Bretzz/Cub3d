/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_pixel_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:51:57 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 18:10:21 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "puts.h"

/* sets the pixel of the passed sprite to the passed color */
void	image_pixel_put(void *image, int x, int y, unsigned int color)
{
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	const void	*addr = mlx_get_data_addr(image,
			&bits_per_pixel, &line_length, &endian);
	const char	*dst = addr
		+ (y * line_length + x * (bits_per_pixel / sizeof(int *)));

	*(unsigned int *)dst = color;
}
