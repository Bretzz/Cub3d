/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:59:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 12:29:57 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* put the player sprite, based on his position and direction */
/* NOTE: ADD BUFFER FOR PRIORITY DISTANCE */
int put_player(t_mlx *mlx, float *pos, float *dir)
{
	const float	our_dir = atan2((mlx->player.pos[1] - pos[1]), (mlx->player.pos[0] - pos[0])) * 180 / M_PI;
	const float   difir = (dir[0] + 180) - our_dir;

	// printf("looking %f, we are at %f, difir %f\n", dir + 180, our_dir, difir);
	if ((difir >= 330 && difir <= 360) || (difir >= 0 && difir <= 30))
		put_sprite_on_map(mlx, pos[0], pos[1], mlx->player.sprite[0]);
	else if (difir >= 210 && difir < 330)
		put_sprite_on_map(mlx, pos[0], pos[1], mlx->player.sprite[3]);
	else if (difir > 30 && difir < 150)
		put_sprite_on_map(mlx, pos[0], pos[1], mlx->player.sprite[2]);
	else
		put_sprite_on_map(mlx, pos[0], pos[1], mlx->player.sprite[1]);
	return (0);
}
