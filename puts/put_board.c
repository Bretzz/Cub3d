/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:56:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/21 18:26:16 by scarlucc         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"
#include "puts.h"

/* 2D PUTS */
// put2d_map(mlx, mlx->map.stats[2], 0x0f4cfa);
// put2d_player(mlx, mlx->player.pos, mlx->map.stats[2], 0x0000FF);
// cast_field(mlx, NULL, &put2d_ray);

/* ! ! ! CALL BEFORE ANY OTHER PUT* ! ! ! */
int	put_board(t_mlx *mlx)
{
	mlx->img->img = mlx_new_image(mlx->mlx, MLX_WIN_X, MLX_WIN_X);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img
			->bits_per_pixel, &mlx->img->line_length, &mlx->img->endian);
	if (!mlx->img->img || !mlx->img->addr)
		return (0);
	mlx->img->bpp = mlx->img->bits_per_pixel >> 3;
	mlx->img->width = MLX_WIN_X;
	mlx->img->heigth = MLX_WIN_Y;
	cast_field(mlx, &put_whole_column, &put2d_ray);
	my_string_put(&mlx->img, 600 , 100, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0xff0000);	//remove
	my_number_put(&mlx->img, 600, 120, -2147483647, 0xff0000);						//remove
	my_number_put(&mlx->img, MLX_WIN_X - 25, 20, mlx->fps, 0xff0000);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	ft_memset(&mlx->img, 0, sizeof(t_img));
	//mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->map.walls[NO].img, 300, 300);
	
	return (1);
}
