/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_board_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:56:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 00:00:22 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* ! ! ! CALL BEFORE ANY OTHER PUT* ! ! ! */
int	put_board(t_mlx *mlx)
{
	char	*fps;

	// ft_printf("board in\n");
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->win_x, mlx->win_y);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img
			.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.img || !mlx->img.addr)
		return (0);

	// put2d_map(mlx, mlx->map.stats[2], 0xff0000);
	// put2d_player(mlx, mlx->map.stats[2], 0x0000FF);
	// cast_field(mlx, &put2d_ray);

	// put_sky_floor(mlx);
	cast_field(mlx, &put_whole_column);
	// ft_printf("field out\n");
	put2d_minimap(mlx, 10);
	// ft_printf("minimap out\n");
	put_sprite_on_map(mlx, 5, 10, mlx->player.sprite[0]);

	float	pos[2] = {10 , 10};
	put_player(mlx, pos, 0);
	// ft_printf("sprite out\n");
	// cast_ray(mlx, mlx->player.pos[0], mlx->player.pos[1], mlx->player.dir[0]);
	// put2d_ray(mlx, 0xa0b000);
	// put_grid(mlx);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	
	// fps counter
	fps = ft_itoa(mlx->fps);
	if (fps == NULL)
		return (0);
	mlx_string_put(mlx->mlx, mlx->win, mlx->win_x - 25, 25, 0xff0000, fps);
	free(fps);
	// ft_printf("board out\n");
	return (1);
}
