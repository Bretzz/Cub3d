/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/08 16:49:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include <stdlib.h>

int clean_exit(t_mlx *mlx);

/* LOBBY MUTEX */
static void	destroy_lobby_sprites(void *mlx_ptr, t_player *lobby)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	// lbb_mutex(1);
	while (i < MAXPLAYERS)
	{
		if (lobby[i].extra != NULL)
		{
			j = 0;
			while (j < SPRITE_NUM)
			{
				mlx_destroy_image(mlx_ptr, ((t_sprite *)(lobby[i].extra))[j].image);
				j++;
			}
			free(lobby[i].extra);
		}
		i++;
	}
	// lbb_mutex(2);
}

/* LOBBY MUTEX */
int	clean_exit(t_mlx *mlx)
{
	char	buffer[MSG_LEN + 6];

	// ft_printf(BOLD"CLEAN_EXIT%s\n", RESET);

	// lbb_mutex(1);
	// print_lobby(mlx->lobby);
	// lbb_mutex(2);

	buffer_player_action(mlx->fake_lobby[mlx->fake_index], "kill", buffer);
	send_all(mlx, buffer, ft_strlen(buffer));

	// destroying sprites
	destroy_lobby_sprites(mlx->mlx, mlx->fake_lobby);

	//freeing mlx resources 
	if (mlx->mlx)
	{
		if(mlx->img.img)
			mlx_destroy_image(mlx->mlx, mlx->img.img);
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
