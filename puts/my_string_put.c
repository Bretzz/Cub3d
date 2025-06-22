/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_string_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:55:15 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 17:20:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "my_puts.h"

void	my_string_put(void *my_struct, int x, int y, const char *string);

static void	put_2by2_square(void *my_struct, int x, int y, unsigned int color)
{
	t_my_img *const	img = (t_my_img *)my_struct;
	const int		bpp = img->bits_per_pixel / sizeof(int *);
	int				t;
	int				s;

	if (my_struct == NULL
		|| img->data == NULL)
		return ;
	t = 0;
	while (t < 2)
	{
		s = 0;
		while (s < 2)
		{
			if (x + t >= 0 && y + s >= 0
				&& x + t < img->width && y + s < img->height)
				*(unsigned int *)(img->data + ((y + s) * img->line_length
							+ (x + t) * bpp)) = color;
			s++;
		}
		t++;
	}
}

/* hardcoded color here */
static void	draw_letter(void *my_struct, int x, int y,
	t_draw_map letter)
{
	int				my_x;
	int				my_y;
	int				i;

	i = 0;
	while (letter.pixel[i][0] != -1)
	{
		my_x = x + letter.pixel[i][0] * 2;
		my_y = y + letter.pixel[i][1] * 2;
		put_2by2_square(my_struct, my_x, my_y, 0xff0000);
		i++;
	}
}

/* 'a' = 97-97 */
/* just upper case letters for now */
void	my_string_put(void *my_struct, int x, int y,
	const char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		draw_letter(my_struct, x, y, get_letter(ft_toupper(string[i])));
		x = x + 12;
		i++;
	}
}
