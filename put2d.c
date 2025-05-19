/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:56:46 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/19 19:21:04 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* put a square in the window, (x, y) are the coordinates
of the top left corner. */
int	put_square(t_mlx *mlx, size_t side, int x, int y, unsigned int color)
{
	int	pixel[2];

	pixel[0] = x;
	while ((size_t)pixel[0] < x + side)
	{
		pixel[1] = y;
		while ((size_t)pixel[1] < y + side)
		{
			my_pixel_put(mlx, pixel[0], pixel[1], color);
			pixel[1]++;
		}
		pixel[0]++;
	}
	return (0);
}
int	put_map(t_mlx *mlx, unsigned int color)
{
	const int	side = mlx->map_dim[2];
	int		i;
	size_t	j;

	i = 0;
	while (mlx->map[i] != NULL)
	{
		j = 0;
		while (mlx->map[i][j] != '\0')
		{
			if (mlx->map[i][j] == '1')
				put_square(mlx, side, i * side, j * side, color);
			j++;
		}
		i++;
	}
	return (0);
}
