/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 17:22:06 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include <stdlib.h>

int	clean_exit(t_mlx *mlx);

/* LOBBY MUTEX */
static void	destroy_lobby_sprites(void *mlx_ptr, t_player *lobby)
{
	unsigned int	i;

	i = 0;
	while (i < MAXPLAYERS)
	{
		if (lobby[i].extra != NULL)
		{
			sprite_destroy(mlx_ptr, lobby[i].extra);
		}
		i++;
	}
}

/* Bonus exit procedure */
int	clean_exit(t_mlx *mlx)
{
	char	buffer[MSG_LEN + 6];

	buffer_player_action(mlx->fake_lobby[mlx->fake_index], "kill", buffer);
	send_all(mlx, buffer, ft_strlen(buffer));
	destroy_lobby_sprites(mlx->mlx, mlx->fake_lobby);
	if (mlx->mlx)
	{
		if (mlx->img.img)
			mlx_destroy_image(mlx->mlx, mlx->img.img);
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		if (mlx->map.mtx)
			free_mtx((void **)mlx->map.mtx);
		free(mlx->mlx);
	}
	hpc_free(mlx->socket, mlx->index, mlx->thread);
	exit(EXIT_SUCCESS);
	return (0);
}
