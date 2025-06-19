/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_number_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:29:27 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/20 00:12:17 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_draw_map
{
	char	digit;
	int		pixel[24][2];
}				t_draw_map;

void	my_number_put(void *my_struct, int x, int y,
	int nb, unsigned int color);

/* one digit is 6x6 */
static t_draw_map get_digit_map(const int digit)
{
	const t_draw_map empty = {42, {{-1,-1}}};
	static const t_draw_map numbers[11] = {
		{'-', {{0,3},{1,3},{2,3},{3,3},{4,3},{5,3},{-1,-1}}},
		{'0', {{1,0},{2,0},{0,1},{0,2},{0,3},{0,4},{1,5},{2,5},{3,1},{3,2},{3,3},{3,4},{-1,-1}}},
		{'1', {{1,0},{0,1},{1,1},{1,2},{1,3},{1,4},{1,5},{0,5},{2,5},{-1,-1}}},
		{'2', {{0,0},{1,0},{2,0},{3,1},{3,2},{2,3},{1,4},{0,5},{1,5},{2,5},{3,5},{-1,-1}}},
		{'3', {{0,0},{1,0},{2,0},{3,1},{1,2},{2,2},{3,3},{3,4},{0,5},{1,5},{2,5},{-1,-1}}},
		{'4', {{3,0},{3,1},{3,2},{3,3},{3,4},{3,5},{0,3},{1,3},{2,3},{2,0},{1,1},{0,2},{-1,-1}}},
		{'5', {{0,0},{1,0},{2,0},{3,0},{0,1},{0,2},{1,2},{2,2},{3,3},{3,4},{0,5},{1,5},{2,5},{-1,-1}}},
		{'6', {{1,0},{2,0},{3,0},{0,1},{0,2},{1,2},{2,2},{0,3},{0,4},{1,5},{2,5},{3,4},{3,3},{-1,-1}}},
		{'7', {{0,0},{1,0},{2,0},{3,0},{3,1},{2,2},{1,3},{1,4},{0,5},{-1,-1}}},
		{'8', {{1,0},{2,0},{0,1},{1,2},{2,2},{3,1},{0,3},{3,3},{0,4},{1,5},{2,5},{3,4},{-1,-1}}},
		{'9', {{1,0},{2,0},{0,1},{3,1},{0,2},{3,2},{1,3},{2,3},{3,3},{3,4},{1,5},{2,5},{-1,-1}}},
	};

	if (digit == -1)
		return (numbers[0]);
	else if (digit < 0 || digit > 9)
		return (empty);
	return (numbers[digit + 1]);
}

static void	put_2by2_square(void *my_struct, int x, int y, unsigned int color)
{
	t_img *const	img = (t_img *)my_struct;
	const int		bpp = img->bits_per_pixel / sizeof(int *);
	int				t;
	int				s;

	if (my_struct == NULL
		|| img->addr == NULL)
		return ;
	t = 0;
	while (t < 2)
	{
		s = 0;
		while (s < 2)
		{
			if (x + t >= 0 && y + s >= 0
				&& x + t < img->width && y + s < img->heigth)
				*(unsigned int *)(img->addr + ((y + s) * img->line_length
							+ (x + t) * bpp)) = color;
			s++;
		}
		t++;
	}
}

static void	draw_digit_map(void *my_struct, int x, int y,
	t_draw_map digit, unsigned int color)
{
	int				my_x;
	int				my_y;
	int				i;

	i = 0;
	while (digit.pixel[i][0] != -1)
	{
		my_x = x + digit.pixel[i][0] * 2;
		my_y = y + digit.pixel[i][1] * 2;
		put_2by2_square(my_struct, my_x, my_y, color);
		i++;
	}
}

/* minus sign to review, also it prints reverse x, also intmin not handled */
void	my_number_put(void *my_struct, int x, int y,
	int nb, unsigned int color)
{
	// if (nb == -2147483648)
	// {
	// 	write(fd, "-2147483648", 11);
	// 	return ;
	// }
	if (nb < 0)
	{
		draw_digit_map(my_struct, x, y, get_digit_map(-1), color);
		x += 12;
		nb *= -1;
	}
	if (nb >= 10)
		my_number_put(my_struct, x - 12, y, nb / 10, color);
	draw_digit_map(my_struct, x, y, get_digit_map(nb % 10), color);
}
