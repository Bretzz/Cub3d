/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 19:09:26 by topiana-         ###   ########.fr       */
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
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);	// macOS issues
	free_mtx((void **)mlx->map.mtx);
	free(mlx->mlx);
	//finally exit
	exit(EXIT_SUCCESS);
	return (0);
}
