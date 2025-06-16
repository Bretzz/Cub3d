/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:59:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/11 17:15:39 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

#define SHOT_FRAMES 10

int	player_put(t_mlx *mlx, t_player *fake_lobby);

/* based on the player dir and our dir */
static int	get_sprite_index(int pos_dir, float our_dir, int action)
{
	const int	difir = (float)(pos_dir + 180.0f) - our_dir;

	if (((difir % 360) >= 330 && (difir % 360) <= 360)
		|| ((difir % 360) >= -30 && (difir % 360) <= 0)
		|| ((difir % 360) >= 0 && (difir % 360) <= 30))
		return (action);
	else if (((difir % 360) > 210 && (difir % 360) < 330)
		|| ((difir % 360) > 210 && (difir % 360) < 330)
		|| ((difir % 360) > -150 && (difir % 360) < -30))
		return (3);
	else if (((difir % 360) > 30 && (difir % 360) < 150)
		|| ((difir % 360) > -330 && (difir % 360) < -210))
		return (2);
	else
		return (1);
	return (0);
}

/* put the player sprite, based on his position and direction */
/* NOTE: ADD BUFFER FOR PRIORITY DISTANCE */
/* idle = 0, shooting = 4 */
static int	one_player_put(t_mlx *mlx, t_player player, int index)
{
	static int	shootframes[MAXPLAYERS];
	t_sprite	*sprite;

	if (mlx->pos_data[index].seen == 0
		|| !lbb_is_alive(player)
		|| player.extra == NULL)
		return (0);
	if (player.data[0] == 4 && shootframes[index] < SHOT_FRAMES)
		shootframes[index]++;
	else if (shootframes[index] == SHOT_FRAMES)
	{
		lbb_mutex(1);
		mlx->lobby[index].data[0] = 0;
		lbb_mutex(2);
		shootframes[index] = 0;
	}
	sprite = &((t_sprite *)player.extra)[get_sprite_index(
			*(float *)&player.tar[0],
			mlx->pos_data[index].dir, player.data[0])];
	sprite->scale = ((MLX_WIN_X / 2) / sprite->heigth)
		/ mlx->pos_data[index].dist;
	ft_memmove(&mlx->pos_data[index], sprite, 3 * sizeof(int));
	put_sprite(mlx, mlx->pos_data[index], *sprite);
	put_health_bar(mlx, mlx->pos_data[index], player.data[1]);
	return (0);
}

/* put the whole lobby's sprites, then clears the pos's data */
int	player_put(t_mlx *mlx, t_player *fake_lobby)
{
	int	i;

	i = 0;
	while (i < MAXPLAYERS)
	{
		one_player_put(mlx, fake_lobby[i], i);
		ft_memset(&mlx->pos_data[i], 0, sizeof(t_plot));
		i++;
	}
	return (0);
}
