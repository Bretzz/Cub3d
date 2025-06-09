/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_board_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:56:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 14:39:24 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

// float	pos[3] = {10, 10, 1};
// put_sprite_on_map(mlx, pos, mlx->player.sprite[1]);
// float	pos2[3] = {7.5f, 2.5f, 1};
// put_sprite_on_map(mlx, pos2, mlx->player.sprite[4]);
// float	pos3[3] = {7.5f, 3.0f, 1};
// put_sprite_on_map(mlx, pos3, mlx->player.sprite[0]);
// float	pos4[3] = {7.5f, 3.5f, 1};
// put_sprite_on_map(mlx, pos4, mlx->player.sprite[1]);
// float	pos5[3] = {7.5f, 4.0f, 1};
// put_sprite_on_map(mlx, pos5, mlx->player.sprite[2]);
// float	pos6[3] = {7.5f, 4.5f, 1};
// put_sprite_on_map(mlx, pos6, mlx->player.sprite[3]);
/* ! ! ! CALL BEFORE ANY OTHER PUT* ! ! ! */
int	put_board(t_mlx *mlx)
{
	int				i;

	mlx->img.img = mlx_new_image(mlx->mlx, MLX_WIN_X, MLX_WIN_Y);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img
			.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.img || !mlx->img.addr)
		return (0);
	cast_field(mlx, &put_whole_column);
	put2d_minimap(mlx, 10);
	i = 0;
	while (i < MAXPLAYERS)
		handle_player(mlx, mlx->fake_lobby, i++);
	put_crosshair(mlx, 0xFF0000);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	ft_memset(&mlx->img, 0, sizeof(t_img));
	put_fps(mlx);
	return (1);
}
