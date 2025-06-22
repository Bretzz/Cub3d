/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_fill_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 05:02:12 by totommi           #+#    #+#             */
/*   Updated: 2025/06/22 17:20:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int		yft_fill_map(char *miniline, t_font *font);

unsigned int	get_pointer_color(char pointer, t_font *font)
{
	unsigned int	i;

	i = 0;
	while (font->table[i].pointer != '\0')
	{
		if (font->table[i].pointer == pointer)
			return (font->table[i].color);
		i++;
	}
	return (VOID);
}

static void	set_row_pixel(int *pixel, int x, int y, int color)
{
	pixel[0] = x;
	pixel[1] = y;
	pixel[2] = color;
}

// "#......#."
static int	get_row_pixels(char *row, const int y, t_font *font, int what)
{
	static int	pixel_count;
	int			color;
	size_t		i;

	if (y == 0)
		pixel_count = 0;
	i = 1;
	while (row[i] != '"')
	{
		if (row[i] == '\0')
			return (1);
		color = get_pointer_color(row[i], font);
		if (color != VOID)
			set_row_pixel(font->ascii_table[what].map[pixel_count++],
				i - 1, y, color);
		i++;
	}
	if (y == font->height - 1)
	{
		font->ascii_table[what].map[pixel_count][0] = -1;
		font->ascii_table[what].map[pixel_count][1] = -1;
	}
	return (0);
}

// {ascii=66,{"#######..","#......#.","#######..","#......#.","#######..",}}
int	yft_fill_map(char *miniline, t_font *font)
{
	const int	what = ft_atoi(&miniline[7]);
	int			y;
	size_t		i;

	font->ascii_table[what].what = what;
	i = 1;
	while (miniline[i] && miniline[i] != '{')
		i++;
	i = i + 1;
	y = 0;
	while (miniline[i] != '\0' && y < font->height
		&& (miniline[i] != '}' || miniline[i + 1] != '}'))
	{
		get_row_pixels(&miniline[i], y, font, what);
		while (miniline[i++] != ',')
		{
			if (miniline[i] == '\0')
				return (1);
		}
		y++;
	}
	if (miniline[i] == '\0')
		return (1);
	return (0);
}
