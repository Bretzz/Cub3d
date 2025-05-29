/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/29 15:36:19 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include <stdlib.h>

int clean_exit(t_mlx *mlx);

int	clean_exit(t_mlx *mlx)
{
	char	buffer[MSG_LEN + 6];
	int		i;

	buffer_player_action(mlx->lobby[*mlx->index], "kill", buffer);
	send_all(mlx, buffer, ft_strlen(buffer), 0);

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
