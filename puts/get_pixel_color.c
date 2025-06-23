/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:38:15 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/23 02:24:23 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "puts.h"

/* takes a image pointer (mlx_xpm_file_to_image()) and the
coordinates of a pixel of that image and returns the color of that pixel.
NOTE: if the pixel (x,y) is out of boundaries it segfaults */

#ifdef __APPLE__

unsigned int	get_pixel_color(void *img_ptr, int x, int y)
{
	t_mlx_img *const	mlx_img = (t_mlx_img *)img_ptr;
	int					bpp;
	int					size_line;
	int					endian;
	char				*data;

	if (x < 0 || x >= mlx_img->width || y < 0 || y >= mlx_img->height)
		return (0);
	data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	return (*(unsigned int *)(data
		+ (y * size_line)
		+ (x * (bpp >> 3))));
}

#else

unsigned int	get_pixel_color(void *img_ptr, int x, int y)
{
	t_img *const	mlx_img = (t_mlx_img *)img_ptr;

	if (x < 0 || x >= mlx_img->width || y < 0 || y >= mlx_img->height)
		return (0);
	return (*(unsigned int *)(mlx->data
		+ (y * mlx->size_line)
		+ (x * (mlx->bpp >> 3))));
}
#endif
