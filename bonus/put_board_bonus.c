/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_board_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:56:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 19:29:51 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ! ! ! CALL BEFORE ANY OTHER PUT* ! ! ! */
int	put_board(t_mlx *mlx)
{	
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->win_x, mlx->win_y);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img
			.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.img || !mlx->img.addr)
		return (0);

	// put2d_map(mlx, mlx->map.stats[2], 0xff0000);
	// put2d_player(mlx, mlx->map.stats[2], 0x0000FF);
	// cast_field(mlx, &put2d_ray);

	put_sky_floor(mlx);
	cast_field(mlx, &put_central_line);
	put2d_minimap(mlx, 10);
	
	put_sprite_on_map(mlx, 5, 10, 0xed80e9);
	// cast_ray(mlx, mlx->player.pos[0], mlx->player.pos[1], mlx->player.dir[0]);
	// put2d_ray(mlx, 0xa0b000);
	// put_grid(mlx);
	
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	
	// fps counter
	mlx_string_put(mlx->mlx, mlx->win, mlx->win_x - 25, 25, 0xff0000, ft_itoa(mlx->fps));
	return (1);
}
