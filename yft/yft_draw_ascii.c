/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_draw_ascii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:26:01 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 17:12:45 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

void	yft_draw_ascii(t_yft_img *img, t_draw_map *map, int *coord, int scale);

static void	draw_scaled_pixel(t_yft_img *img,
	int *pixel, unsigned int color, int scale)
{
	int	t;
	int	s;

	t = 0;
	while (t < scale)
	{
		s = 0;
		while (s < scale)
		{
			if (pixel[0] + t < img->width && pixel[1] + s < img->heigth)
			{
				*(unsigned int *)(img->addr
						+ (((pixel[1] + s) * img->line_length)
							+ ((pixel[0] + t) * img->bpp))) = color;
			}
			s++;
		}
		t++;
	}
}

void	yft_draw_ascii(t_yft_img *img, t_draw_map *map, int *coord, int scale)
{
	int	pixel[2];
	int	i;

	if (map->what == '\0')
		return ;
	i = 0;
	while (map->map[i][0] != -1)
	{
		pixel[0] = coord[0] + (map->map[i][0]) * scale;
		pixel[1] = coord[1] + (map->map[i][1]) * scale;
		if (pixel[0] >= 0 && pixel[0] < img->width
			&& pixel[1] >= 0 && pixel[1] < img->heigth
			&& map->map[i][2] != VOID)
			draw_scaled_pixel(img, pixel, map->map[i][2], scale);
		i++;
	}
}
