/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_walls_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 02:31:34 by totommi           #+#    #+#             */
/*   Updated: 2025/06/22 17:20:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load_single_wall(void *mlx_ptr, t_my_img *wall, char *path)
{
	wall->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &wall->width,
			&wall->height);
	if (wall->img_ptr == NULL)
		return (1);
	wall->data = mlx_get_data_addr(wall->img_ptr, &wall->bits_per_pixel,
			&wall->line_length, &wall->endian);
	wall->bpp = wall->bits_per_pixel >> 3;
	return (0);
}

int	load_walls_texture(t_mlx *mlx)
{
	if (load_single_wall(mlx->mlx, &mlx->map.walls[NO], mlx->map.no_wall))
		return (1);
	if (load_single_wall(mlx->mlx, &mlx->map.walls[SO], mlx->map.so_wall))
		return (1);
	if (load_single_wall(mlx->mlx, &mlx->map.walls[EA], mlx->map.ea_wall))
		return (1);
	if (load_single_wall(mlx->mlx, &mlx->map.walls[WE], mlx->map.we_wall))
		return (1);
	return (0);
}
