/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_string_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:19:47 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 16:51:30 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int	yft_string_put(void *img_ptr, int x, int y, const char *string);

static t_font	*get_any_font(void)
{
	t_font *const	fonts = yft_font_db(0);
	unsigned int	i;

	i = 0;
	while (i < 10)
	{
		if (fonts[i].name[0] != '\0')
			return (&fonts[i]);
		i++;
	}
	return (NULL);
}

/* font is arbitrairly choosen for now... */
/* data is formatted like this:
	data[0] = x,
	data[1] = y,
	data[2] = img width
	data[3] = img heigth */
/* right now scale is 1 */
int	yft_string_put(void *img_ptr, int x, int y, const char *string)
{
	t_font *const	font = get_any_font();
	t_yft_img		my_img;
	size_t			i;
	const int		scale = 2;
	int				coord[2];

	if (font == NULL)
	{
		ft_printfd(2, "yft: No font found\n");
		return (1);
	}
	coord[0] = x;
	coord[1] = y;
	i = 0;
	img_get_data(img_ptr, &my_img);
	while (string[i] != '\0')
	{
		yft_draw_ascii(&my_img, &font->ascii_table[(int)string[i]],
			coord, scale);
		if (string[i++ + 1] != '\0')
			fill_spacing(&my_img, font, coord, scale);
		coord[0] = coord[0] + (font->width + font->space) * scale;
	}
	return (0);
}
