/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:56:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 13:31:42 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "puts.h"

/* 2D PUTS */
// put2d_map(mlx, mlx->map.stats[2], 0x0f4cfa);
// put2d_player(mlx, mlx->player.pos, mlx->map.stats[2], 0x0000FF);
// cast_field(mlx, NULL, &put2d_ray);

/* ! ! ! CALL BEFORE ANY OTHER PUT* ! ! ! */
int	put_board(t_mlx *mlx)
{
	mlx->img->img_ptr = mlx_new_image(mlx->mlx, MLX_WIN_X, MLX_WIN_X);
	if (!mlx->img->img_ptr)
		return (0);
	mlx->img->data = mlx_get_data_addr(mlx->img->img_ptr, &mlx->img
			->bits_per_pixel, &mlx->img->line_length, &mlx->img->endian);
	mlx->img->bpp = mlx->img->bits_per_pixel >> 3;
	mlx->img->width = MLX_WIN_X;
	mlx->img->heigth = MLX_WIN_Y;
	cast_field(mlx, &put_whole_column, NULL);
	my_number_put(&mlx->img, MLX_WIN_X - 25, 20, mlx->fps);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img_ptr, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img->img_ptr);
	ft_memset(&mlx->img, 0, sizeof(t_my_img));
	return (1);
}
