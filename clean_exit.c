/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/23 16:45:17 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

int clean_exit(t_mlx *mlx);

int	clean_exit(t_mlx *mlx)
{
	//freeing mlx resources 
	if (mlx->player.sprite != NULL)
		mlx_destroy_image(mlx->mlx, mlx->player.sprite);	//for freeing sprites
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);	// macOS issues
		//free_mtx((void **)mlx->map.mtx);
		if (mlx->map.mtx)
			free_mtx((void **)mlx->map.mtx);
		free(mlx->mlx);
	}
	//finally exit
	exit(EXIT_SUCCESS);
	return (0);
}
