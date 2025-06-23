/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/23 02:21:22 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>

int	clean_exit(t_mlx *mlx, int exit_code);

static void	destroy_wall_data(t_mlx *mlx)
{
	if (mlx->map.walls[NO].img_ptr)
		mlx_destroy_image(mlx->mlx, mlx->map.walls[NO].img_ptr);
	if (mlx->map.walls[SO].img_ptr)
		mlx_destroy_image(mlx->mlx, mlx->map.walls[SO].img_ptr);
	if (mlx->map.walls[EA].img_ptr)
		mlx_destroy_image(mlx->mlx, mlx->map.walls[EA].img_ptr);
	if (mlx->map.walls[WE].img_ptr)
		mlx_destroy_image(mlx->mlx, mlx->map.walls[WE].img_ptr);
	if (mlx->map.no_wall)
		free(mlx->map.no_wall);
	if (mlx->map.so_wall)
		free(mlx->map.so_wall);
	if (mlx->map.we_wall)
		free(mlx->map.we_wall);
	if (mlx->map.ea_wall)
		free(mlx->map.ea_wall);
}

int	clean_exit(t_mlx *mlx, int exit_code)
{
	destroy_wall_data(mlx);
	if (mlx->mlx)
	{
		if (mlx->img->img_ptr)
			mlx_destroy_image(mlx->mlx, mlx->img->img_ptr);
		if (mlx->win)
		{
			mlx_destroy_window(mlx->mlx, mlx->win);
			mlx->win = NULL;
		}
		if (__LINUX__)
			// mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	if (mlx->map.mtx)
		free_mtx((void **)mlx->map.mtx);
	exit(exit_code);
	return (0);
}
