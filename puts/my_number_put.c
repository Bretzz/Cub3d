/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_number_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:29:27 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 17:20:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "my_puts.h"

void	my_number_put(void *my_struct, int x, int y, int nb);

/* one digit is 6x6 */
static t_draw_map	get_digit_map(const int digit)
{
	const t_draw_map		empty = {42, {{-1, -1}}};
	static const t_draw_map	numbers[11] = {
	{'-', {{1, 3}, {2, 3}, {3, 3}, {4, 3}, {-1, -1}}}, {'0', {{1, 0}, {2, 0},
	{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 5}, {2, 5}, {3, 1}, {3, 2}, {3, 3},
	{3, 4}, {-1, -1}}}, {'1', {{1, 0}, {0, 1}, {1, 1}, {1, 2}, {1, 3}, {1, 4},
	{1, 5}, {0, 5}, {2, 5}, {-1, -1}}}, {'2', {{0, 0}, {1, 0}, {2, 0}, {3, 1},
	{3, 2}, {2, 3}, {1, 4}, {0, 5}, {1, 5}, {2, 5}, {3, 5}, {-1, -1}}}, {'3',
	{{0, 0}, {1, 0}, {2, 0}, {3, 1}, {1, 2}, {2, 2}, {3, 3}, {3, 4}, {0, 5},
	{1, 5}, {2, 5}, {-1, -1}}}, {'4', {{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4},
	{3, 5}, {0, 3}, {1, 3}, {2, 3}, {2, 0}, {1, 1}, {0, 2}, {-1, -1}}}, {'5',
	{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}, {3, 3},
	{3, 4}, {0, 5}, {1, 5}, {2, 5}, {-1, -1}}}, {'6', {{1, 0}, {2, 0}, {3, 0},
	{0, 1}, {0, 2}, {1, 2}, {2, 2}, {0, 3}, {0, 4}, {1, 5}, {2, 5}, {3, 4},
	{3, 3}, {-1, -1}}}, {'7', {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {3, 1}, {2, 2},
	{1, 3}, {1, 4}, {0, 5}, {-1, -1}}}, {'8', {{1, 0}, {2, 0}, {0, 1}, {1, 2},
	{2, 2}, {3, 1}, {0, 3}, {3, 3}, {0, 4}, {1, 5}, {2, 5}, {3, 4}, {-1, -1}}},
	{'9', {{1, 0}, {2, 0}, {0, 1}, {3, 1}, {0, 2}, {3, 2}, {1, 3}, {2, 3},
	{3, 3}, {3, 4}, {1, 5}, {2, 5}, {-1, -1}}}};

	if (digit == -1)
		return (numbers[0]);
	else if (digit < 0 || digit > 9)
		return (empty);
	return (numbers[digit + 1]);
}

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
static void	draw_digit_map(void *my_struct, int x, int y,
	t_draw_map digit)
{
	int				my_x;
	int				my_y;
	int				i;

	i = 0;
	while (digit.pixel[i][0] != -1)
	{
		my_x = x + digit.pixel[i][0] * 2;
		my_y = y + digit.pixel[i][1] * 2;
		put_2by2_square(my_struct, my_x, my_y, 0xff0000);
		i++;
	}
}

/* :D */
static void	brute_force_int_max(void *my_struct, int x, int y)
{
	draw_digit_map(my_struct, x, y, get_digit_map(-1));
	draw_digit_map(my_struct, x + 12, y, get_digit_map(2));
	draw_digit_map(my_struct, x + 24, y, get_digit_map(1));
	draw_digit_map(my_struct, x + 36, y, get_digit_map(4));
	draw_digit_map(my_struct, x + 48, y, get_digit_map(7));
	draw_digit_map(my_struct, x + 60, y, get_digit_map(4));
	draw_digit_map(my_struct, x + 72, y, get_digit_map(8));
	draw_digit_map(my_struct, x + 84, y, get_digit_map(3));
	draw_digit_map(my_struct, x + 96, y, get_digit_map(6));
	draw_digit_map(my_struct, x + 108, y, get_digit_map(4));
	draw_digit_map(my_struct, x + 120, y, get_digit_map(8));
}

/* PERFECT */
void	my_number_put(void *my_struct, int x, int y,
	int nb)
{
	static int			digits;
	int					my_digit;
	char				sign;

	if (nb == -2147483648)
	{
		brute_force_int_max(my_struct, x, y);
		return ;
	}
	sign = 0;
	if (nb < 0)
	{
		sign = 1;
		digits++;
		nb *= -1;
	}
	my_digit = ++digits;
	if (nb >= 10)
		my_number_put(my_struct, x - 12, y, nb / 10);
	if (sign != 0)
		draw_digit_map(my_struct, x, y, get_digit_map(-1));
	draw_digit_map(my_struct, x + (12 * (digits - 1)), y,
		get_digit_map(nb % 10));
	if (my_digit == sign + 1)
		digits = 0;
}
