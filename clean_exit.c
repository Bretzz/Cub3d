/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 22:18:36 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

int clean_exit(t_mlx *mlx);

int	clean_exit(t_mlx *mlx)
{
	//freeing mlx resources 
	mlx_destroy_window(mlx->mlx, mlx->win);
	// mlx_destroy_display(mlx->mlx);	// macOS issues
	free_mtx((void **)mlx->map.mtx);
	free(mlx->mlx);
	//finally exit
	exit(EXIT_SUCCESS);
	return (0);
}
