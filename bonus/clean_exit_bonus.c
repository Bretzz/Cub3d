/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:02:14 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/06 17:58:17 by topiana-         ###   ########.fr       */
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
	lbb_mutex(1);
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(lobby[i]) && lobby[i].extra != NULL)
		{
			j = 0;
			while (j < SPRITE_NUM)
			{
				mlx_destroy_image(mlx_ptr, ((t_sprite *)(lobby[i].extra))[j].image);
				j++;
			}
		}
		i++;
	}
	lbb_mutex(2);
}

/* LOBBY MUTEX */
int	clean_exit(t_mlx *mlx)
{
	char	buffer[MSG_LEN + 6];

	buffer_player_action(mlx->fake_lobby[*mlx->index], "kill", buffer);
	send_all(mlx, buffer, ft_strlen(buffer));

	// destroying sprites
	destroy_lobby_sprites(mlx->mlx, mlx->lobby);

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
