/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_board_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:56:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 02:55:17 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* puts the image and cleanups the t_img struct */
static void	img_put_and_clean(t_mlx *mlx, t_my_img *img, int offset)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, img->img_ptr, offset, offset);
	mlx_destroy_image(mlx->mlx, img->img_ptr);
	ft_memset(img, 0, sizeof(t_my_img));
}

/* initialize the t_img struct */
static int	img_init(void *mlx_ptr, t_my_img *img, int size_x, int size_y)
{
	img->img_ptr = mlx_new_image(mlx_ptr, size_x, size_y);
	if (!img->img_ptr)
		return (0);
	img->data = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->width = size_x;
	img->heigth = size_y;
	img->bpp = img->bits_per_pixel >> 3;
	return (1);
}

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
	player_handle(mlx, mlx->fake_lobby);
	if (!img_init(mlx->mlx, &mlx->img[0], MLX_WIN_X, MLX_WIN_Y))
		return (0);
	if (mlx->keys.minimap)
	{
		if (!img_init(mlx->mlx, &mlx->img[1],
				mlx->map.mini_side * mlx->map.stats[0],
				mlx->map.mini_side * mlx->map.stats[1]))
			return (0);
		put2d_minimap(mlx, mlx->map.mini_side);
		cast_field(mlx, &put_whole_column, &put2d_mini_ray);
		put2d_mini_lobby(mlx, mlx->map.mini_side);
	}
	else
		cast_field(mlx, &put_whole_column, NULL);
	player_put(mlx, mlx->fake_lobby);
	put_crosshair(mlx, 0xFF0000);
	img_put_and_clean(mlx, &mlx->img[0], 0);
	if (mlx->keys.minimap)
		img_put_and_clean(mlx, &mlx->img[1], MINIMAP_OFFSET);
	put_fps(mlx);
	return (1);
}
