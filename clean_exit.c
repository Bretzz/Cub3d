/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/21 19:07:35 by scarlucc         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"
#include <stdlib.h>

int clean_exit(t_mlx *mlx, int exit_code);

int	clean_exit(t_mlx *mlx, int exit_code)
{
	if (mlx->win)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx->win = NULL;
	}
	//free sprite pointers (repeat for every sprite)
	if (mlx->map.walls[NO].img)
		mlx_destroy_image(mlx->mlx, mlx->map.walls[NO].img);
	if (mlx->map.walls[SO].img)
		mlx_destroy_image(mlx->mlx, mlx->map.walls[SO].img);
	if (mlx->map.walls[EA].img)
		mlx_destroy_image(mlx->mlx, mlx->map.walls[EA].img);
	if (mlx->map.walls[WE].img)
		mlx_destroy_image(mlx->mlx, mlx->map.walls[WE].img);
	
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
		if (mlx->mlx)
		{
			if(__LINUX__)
				mlx_destroy_display(mlx->mlx);
			free(mlx->mlx);
		}
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
	
	
	
	//finally exit
	exit(exit_code);
	return (0);
}
