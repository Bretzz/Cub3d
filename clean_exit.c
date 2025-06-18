/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 12:40:49 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>

int clean_exit(t_mlx *mlx);

int	clean_exit(t_mlx *mlx)
{
	if (mlx->win)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx->win = NULL;
	}
		
	//freeing mlx resources 
	if (mlx->mlx)
	{
		if(mlx->img->img)
			mlx_destroy_image(mlx->mlx, mlx->img->img);
		if (mlx->win)
		{
			mlx_destroy_window(mlx->mlx, mlx->win);
			mlx->win = NULL;
		}
			
		mlx_destroy_display(mlx->mlx);	// macOS issues
		free(mlx->mlx);
	}
	if (mlx->map.mtx)
		free_mtx((void **)mlx->map.mtx);
	if (mlx->map.no_wall)
		free(mlx->map.no_wall);
	if (mlx->map.so_wall)
		free(mlx->map.so_wall);
	if (mlx->map.we_wall)
		free(mlx->map.we_wall);
	if (mlx->map.ea_wall)
		free(mlx->map.ea_wall);
	//aggiungi altri muri e pavimento e soffitto
	
	//finally exit
	exit(EXIT_SUCCESS);
	return (0);
}
