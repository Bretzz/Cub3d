/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/11 02:13:55 by totommi          ###   ########.fr       */
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

/* sends the 'host' msg if we are host */
int	resign_exit(t_mlx *mlx)
{
	if (DEBUG)
		ft_printf("resigning...\n");
	char	buffer[MSG_LEN + 9];
	int		new_host;

	if (mlx->fake_index == HOST)
	{
		new_host = 1;
		while (!lbb_is_alive(mlx->fake_lobby[new_host]))
			new_host++;
		buffer_player_action(mlx->fake_lobby[new_host], "host", buffer);
		send_all(mlx, buffer, ft_strlen(buffer));
	}
	clean_exit(mlx);
	return (0);
}

/* Bonus exit procedure */
int	clean_exit(t_mlx *mlx)
{
	char	buffer[MSG_LEN + 9];

	buffer_player_action(mlx->fake_lobby[mlx->fake_index], "kill", buffer);
	send_all(mlx, buffer, ft_strlen(buffer));
	hpc_free(mlx->socket, mlx->index, mlx->thread);
	destroy_lobby_sprites(mlx->mlx, mlx->fake_lobby);
	if (mlx->mlx)
	{
		if (mlx->img[0].img)
			mlx_destroy_image(mlx->mlx, mlx->img[0].img);
		if (mlx->img[1].img)
			mlx_destroy_image(mlx->mlx, mlx->img[1].img);
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		// mlx_destroy_display(mlx->mlx);
		if (mlx->map.mtx)
			free_mtx((void **)mlx->map.mtx);
		free(mlx->mlx);
	}
	// hpc_free(mlx->socket, mlx->index, mlx->thread);
	exit(EXIT_SUCCESS);
	return (0);
}
