/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:38:15 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 13:31:29 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "mlx_int.h"
#include "puts.h"

/* takes a image pointer (mlx_xpm_file_to_image()) and the
coordinates of a pixel of that image and returns the color of that pixel.
NOTE: if the pixel (x,y) is out of boundaries it segfaults */
unsigned int	get_pixel_color(void *img_ptr, int x, int y)
{
	t_img *const	mlx_img = (t_img *)img_ptr;

	if (x < 0 || x >= mlx_img->width || y < 0 || y >= mlx_img->height)
		return (0);
	return (*(unsigned int *)(mlx_img->data
		+ (y * mlx_img->size_line)
		+ (x * (mlx_img->bpp >> 3))));
}
