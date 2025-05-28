/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 01:54:28 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
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
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	//freeing mlx resources 
	if (mlx->mlx)
	{
		// mlx_destroy_display(mlx->mlx);	// macOS issues
		//free_mtx((void **)mlx->map.mtx);
		if (mlx->map.mtx)
			free_mtx((void **)mlx->map.mtx);
		free(mlx->mlx);
	}
	//finally exit
	exit(EXIT_SUCCESS);
	return (0);
}
