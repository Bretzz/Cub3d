/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:59:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/10 15:51:10 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* put the player sprite, based on his position and direction */
/* NOTE: ADD BUFFER FOR PRIORITY DISTANCE */
/* idle = 0, shooting = 4 */
int	put_player(t_mlx *mlx, t_player player, int action)
{
	const float	our_dir = atan2((mlx->player.pos[1] - *(float *)&player.pos[1]),
			(mlx->player.pos[0] - *(float *)&player.pos[0])) * 180 / M_PI;
	const int	difir = (float)(*(float *)&player.tar[0] + 180.0f) - our_dir;
	int			sprite_index;

	sprite_index = 0;
	if (((difir % 360) >= 330 && (difir % 360) <= 360)
		|| ((difir % 360) >= -30 && (difir % 360) <= 0)
		|| ((difir % 360) >= 0 && (difir % 360) <= 30))
		sprite_index = action;
	else if (((difir % 360) > 210 && (difir % 360) < 330)
		|| ((difir % 360) > 210 && (difir % 360) < 330)
		|| ((difir % 360) > -150 && (difir % 360) < -30))
		sprite_index = 3;
	else if (((difir % 360) > 30 && (difir % 360) < 150)
		|| ((difir % 360) > -330 && (difir % 360) < -210))
		sprite_index = 2;
	else
		sprite_index = 1;
	put_sprite_on_map(mlx, (float *)player.pos,
		((t_sprite *)player.extra)[sprite_index]);
	if (mlx->player.last_sprite_data.scale != 0)
		put_health_bar(mlx, mlx->player.last_sprite_data, player.data[1]);
	return (0);
}
