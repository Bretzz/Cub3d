/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2d_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:36:25 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/30 14:34:03 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* puts the minimap and the single player
location/direction */
/* LOBBY MUTEX */
int	put2d_minimap(t_mlx *mlx, size_t side)
{
	put2d_map(mlx, side, 0x0000ff);
	put2d_player(mlx, mlx->player.pos, side, 0xff0000);
	// ft_printf("minimap in\n");
	cast_ray(mlx, mlx->player.pos[0], mlx->player.pos[1], mlx->player.dir[0]);
	// ft_printf("minimap out\n");
	put2d_ray(mlx, side, 0, 0x00ff00);
	// ft_printf("2dray out\n");
	return (0);
}
