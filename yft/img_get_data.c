/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:40:05 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/23 02:31:03 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"
#ifndef __APPLE__
# include "mlx_int.h"

void	img_get_data(void *img_ptr, t_yft_img *img)
{
	t_img *const	mlx_img = (t_img *)img_ptr;

	img->img = img_ptr;
	img->addr = mlx_img->data;
	img->bits_per_pixel = mlx_img->bpp;
	img->line_length = mlx_img->size_line;
	img->endian = mlx_img->image->byte_order;
	img->height = mlx_img->height;
	img->width = mlx_img->width;
	img->bpp = img->bits_per_pixel >> 3;
}

#else

void	img_get_data(void *img_ptr, t_yft_img *img)
{
	t_mlx_img *const	mlx_img = (t_mlx_img *)img_ptr;

	img->img = img_ptr;
	img->addr = mlx_get_data_addr(img_ptr,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian);
	img->height = mlx_img->height;
	img->width = mlx_img->width;
	img->bpp = img->bits_per_pixel >> 3;
}
#endif
