/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:56:46 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 22:18:06 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* put a square in the window, (x, y) are the coordinates
of the top left corner. */
int	put_square(t_mlx *mlx, size_t side, int x, int y, unsigned int color)
{
	int	pixel[2];

//	ft_printf("putting square (%d, %d) of side %u\n", x, y, side);
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

int	put2d_map(t_mlx *mlx, int side, unsigned int color)
{
	int		i;
	size_t	j;

	i = 0;
	while (mlx->map.mtx[i] != NULL)
	{
		j = 0;
		while (mlx->map.mtx[i][j] != '\0')
		{
			if (mlx->map.mtx[i][j] == '1')
				put_square(mlx, side, j * side, i * side, color);
			j++;
		}
		i++;
	}
	return (0);
}

/* side is the length of the single square unit in pixel */
int	put2d_player(t_mlx *mlx, int side, unsigned int color)
{
	put_square(mlx,
		side / 2,
		mlx->player.pos[0] * side,
		mlx->player.pos[1] * side,
		color);
	return (0);
}

int	put2d_ray(void *my_struct, int side, float null2, unsigned int color)
{
	t_mlx	*const mlx = (t_mlx *)my_struct;
	int ray[2];
	int	pos[2];

	(void)null2;
	if (mlx->ray[0] != 0 || mlx->ray[1] != 0)
	{
		ray[0] = mlx->ray[0] * side;
		ray[1] = mlx->ray[1] * side;
		pos[0] = mlx->player.pos[0] * side;
		pos[1] = mlx->player.pos[1] * side;
		put_line(mlx, pos, ray, color);
	}
	return (0);
}

int	put2d_minimap(t_mlx *mlx, size_t side)
{
	put2d_map(mlx, side, 0x0000ff);
	put2d_player(mlx, side, 0xff0000);
	cast_ray(mlx, mlx->player.pos[0], mlx->player.pos[1], mlx->player.dir[0]);
	put2d_ray(mlx, side, 0, 0x00ff00);
	return (0);
}
