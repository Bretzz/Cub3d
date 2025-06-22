/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 13:31:48 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include <stdlib.h>

int	clean_exit(t_mlx *mlx, int exit_code);

static void	destroy_walls_textures(void *mlx_ptr, t_my_img *walls)
{
	unsigned int	i;

	i = 0;
	while (i < 4)
	{
		if (walls[i].img_ptr != NULL)
			mlx_destroy_image(mlx_ptr, walls[i].img_ptr);
		i++;
	}
}

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
	char	buffer[MSG_LEN + 9];
	int		new_host;

	if (DEBUG)
		ft_printf("resigning...\n");
	if (mlx->fake_index == HOST)
	{
		new_host = 1;
		while (!lbb_is_alive(mlx->fake_lobby[new_host]))
			new_host++;
		if (new_host < MAXPLAYERS)
		{
			buffer_player_action(mlx->fake_lobby[new_host], "host", buffer);
			send_all(mlx, buffer, ft_strlen(buffer));
		}
	}
	clean_exit(mlx, EXIT_SUCCESS);
	return (0);
}

/* Bonus exit procedure */
int	clean_exit(t_mlx *mlx, int exit_code)
{
	char	buffer[MSG_LEN + 9];

	buffer_player_action(mlx->fake_lobby[mlx->fake_index], "kill", buffer);
	send_all(mlx, buffer, ft_strlen(buffer));
	hpc_free(mlx->socket, mlx->index, mlx->thread);
	destroy_lobby_sprites(mlx->mlx, mlx->fake_lobby);
	destroy_walls_textures(mlx->mlx, mlx->map.walls);
	if (mlx->mlx)
	{
		if (mlx->img[0].img_ptr)
			mlx_destroy_image(mlx->mlx, mlx->img[0].img_ptr);
		if (mlx->img[1].img_ptr)
			mlx_destroy_image(mlx->mlx, mlx->img[1].img_ptr);
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free_mtx((void **)mlx->map.mtx);
	free(mlx->map.no_wall);
	free(mlx->map.so_wall);
	free(mlx->map.we_wall);
	free(mlx->map.ea_wall);
	exit(exit_code);
	return (0);
}
