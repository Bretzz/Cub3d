/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:38:15 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/07 16:44:32 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* takes a image pointer (mlx_xpm_file_to_image()) and the
coordinates of a pixel of that image and returns the color of that pixel.
NOTE: if the pixel (x,y) is out of boundaries it segfaults */
unsigned int	get_pixel_color(void *image, int x, int y)
{
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	const void	*addr = mlx_get_data_addr(image,
			&bits_per_pixel, &line_length, &endian);
	const char	*dst = addr
		+ (y * line_length + x * (bits_per_pixel / sizeof(int *)));

	return (*(unsigned int *)dst);
}
