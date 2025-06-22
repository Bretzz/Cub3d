/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_img_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:19:19 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 15:06:29 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

t_yft_img	yft_img_init(void *mlx_ptr, int length, int heigth);

t_yft_img	yft_img_init(void *mlx_ptr, int length, int heigth)
{
	t_yft_img	new_img;

	new_img.img = mlx_new_image(mlx_ptr, length, heigth);
	if (new_img.img == NULL)
		return (new_img);
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel,
			&new_img.line_length, &new_img.endian);
	new_img.width = length;
	new_img.heigth = heigth;
	new_img.bpp = new_img.bits_per_pixel >> 3;
	return (new_img);
}
