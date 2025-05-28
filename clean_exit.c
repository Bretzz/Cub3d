/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 12:37:23 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>

int clean_exit(t_mlx *mlx);

int	clean_exit(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	//freeing mlx resources 
	if (mlx->mlx)
	{
		//free_mtx((void **)mlx->map.mtx);
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);	// macOS issues
		free(mlx->mlx);
	}
	if (mlx->map.mtx)
			free_mtx((void **)mlx->map.mtx);
	if (mlx->map.no_wall)
		free(mlx->map.no_wall);
	//finally exit
	exit(EXIT_SUCCESS);
	return (0);
}
