/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 18:17:56 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include <stdlib.h>

int clean_exit(t_mlx *mlx);

int	clean_exit(t_mlx *mlx)
{
	int	i;

	// destroying sprites
	i = 0;
	while (i < 4)
	{
		if (mlx->player.sprite[i].image != NULL)
			mlx_destroy_image(mlx->mlx, mlx->player.sprite[i].image);
		i++;
	}
	//freeing mlx resources 
	if (mlx->mlx)
	{
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
			//free_mtx((void **)mlx->map.mtx);
		mlx_destroy_display(mlx->mlx);	// macOS issues
		if (mlx->map.mtx)
			free_mtx((void **)mlx->map.mtx);
		free(mlx->mlx);
	}
	hpc_free(mlx->socket, mlx->index, mlx->thread);
	//finally exit
	exit(EXIT_SUCCESS);
	return (0);
}
