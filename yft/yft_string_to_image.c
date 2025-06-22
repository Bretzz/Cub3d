/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_string_to_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:47:52 by totommi           #+#    #+#             */
/*   Updated: 2025/06/22 15:51:52 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

void	*yft_string_to_image(void *mlx_ptr, const char *font_name,
			const char *string, int scale);

static t_font	*get_font_by_name(const char *font)
{
	t_font *const	fonts = yft_font_db(0);
	unsigned int	i;

	i = 0;
	while (i < 10)
	{
		if (!ft_strcmp(font, fonts[i].name))
			return (&fonts[i]);
		i++;
	}
	return (NULL);
}

/* font:string */
void	*yft_string_to_image(void *mlx_ptr, const char *font_name,
	const char *string, int scale)
{
	t_font *const	font = get_font_by_name(font_name);
	t_yft_img		img;
	size_t			i;
	int				coord[2];

	if (font == NULL)
	{
		ft_printfd(2, "yft: Invalid font\n");
		return (NULL);
	}
	img = yft_img_init(mlx_ptr, ft_strlen(string)
			* (font->width + font->space) * scale,
			font->heigth * scale);
	if (img.img == NULL)
		return (NULL);
	ft_memset(coord, 0, 2 * sizeof(int));
	i = 0;
	while (string[i] != '\0')
	{
		yft_draw_ascii(&img, &font->ascii_table[(int)string[i]], coord, scale);
		if (string[i++ + 1] != '\0')
			fill_spacing(&img, font, coord, scale);
		coord[0] = coord[0] + (font->width + font->space) * scale;
	}
	return (img.img);
}
