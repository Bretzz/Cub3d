/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:56:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/27 23:54:30 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/* 2D PUTS */
// put2d_map(mlx, mlx->map_dim[2], 0xff0000);
// put2d_player(mlx, mlx->map_dim[2], 0x0000FF);
// cast_field(mlx, &put2d_ray);
/* ! ! ! CALL BEFORE ANY OTHER PUT* ! ! ! */
int	put_board(t_mlx *mlx)
{
	char	*fps;

	mlx->img.img = mlx_new_image(mlx->mlx, mlx->win_x, mlx->win_y);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img
			.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.img || !mlx->img.addr)
		return (0);
	
	// plotting the screen
	cast_field(mlx, &put_whole_column);
	put2d_minimap(mlx, 10);

	// freeing resources
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);

	// plotting the FPS
	fps = ft_itoa(mlx->fps);
	if (fps == NULL)
		return (0);
	mlx_string_put(mlx->mlx, mlx->win, mlx->win_x - 25, 25, 0xff0000, fps);
	free(fps);
	return (1);
}
