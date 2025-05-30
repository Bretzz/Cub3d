/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:59:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/30 14:38:55 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* put the player sprite, based on his position and direction */
/* NOTE: ADD BUFFER FOR PRIORITY DISTANCE */
/* idle = 0, shooting = 4 */
int put_player(t_mlx *mlx, t_player player, int action/* , int chroma */)
{
	const float	our_dir = atan2((mlx->player.pos[1] - *(float *)&player.pos[1]), (mlx->player.pos[0] - *(float *)&player.pos[0])) * 180 / M_PI;
	const int   difir = (float)(*(float *)&player.tar[0] + 180.0f) - our_dir;
	int			sprite_index;

	sprite_index = 0;
	// printf("looking %f, we are at %f, difir %d\n", dir[0] + 180, our_dir, difir);
	if (((difir % 360) >= 330 && (difir % 360) <= 360)
		|| ((difir % 360) >= -30 && (difir % 360) <= 0) || ((difir % 360) >= 0 && (difir % 360) <= 30))
		sprite_index = action;
		// put_sprite_on_map(mlx, (float *)player.pos, mlx->player.sprite[action], player.hp);
	else if (((difir % 360) > 210 && (difir % 360) < 330) || ((difir % 360) > 210 && (difir % 360) < 330)
		|| ((difir % 360) > -150 && (difir % 360) < -30))
		sprite_index = 3;
		// put_sprite_on_map(mlx, (float *)player.pos, mlx->player.sprite[3], player.hp);
	else if (((difir % 360) > 30 && (difir % 360) < 150)
		|| ((difir % 360) > -330 && (difir % 360) < -210))
		sprite_index = 2;
		// put_sprite_on_map(mlx, (float *)player.pos, mlx->player.sprite[2], player.hp);
	else
		sprite_index = 1;
		// put_sprite_on_map(mlx, (float *)player.pos, mlx->player.sprite[1], player.hp);
	put_sprite_on_map(mlx, (float *)player.pos, ((t_sprite *)player.extra)[sprite_index]/* , chroma */);
	if (mlx->player.last_sprite_data.scale != 0)
		put_health_bar(mlx, mlx->player.last_sprite_data, player.hp);
	// printf("final dist %f, final scale %f\n", mlx->player.last_sprite_data.dist, mlx->player.last_sprite_data.scale);
	return (0);
}
