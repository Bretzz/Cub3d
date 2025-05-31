/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2d_minimap_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:37:13 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/31 16:03:43 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* puts the minimap and the single player
location/direction */
/* LOBBY MUTEX */
int	put2d_minimap(t_mlx *mlx, size_t side)
{
    int i;

	put2d_map(mlx, side, 0x0000ff);
    i = 0;
    while (i < MAXPLAYERS)
    {
        if (lbb_is_alive(mlx->fake_lobby[i]) && mlx->fake_lobby[i].extra != NULL)
        {
            put2d_player(mlx, (float *)mlx->fake_lobby[i].pos, side, ((t_sprite *)mlx->fake_lobby[i].extra)[0].chroma);
        }
        i++;
    }
    cast_ray(mlx, mlx->player.pos[0], mlx->player.pos[1], mlx->player.dir[0]);
    // ft_printf("minimap out\n");
    // ft_printf("A\n");
    // ft_printf("B\n");
    put2d_ray(mlx, side, 0, mlx->player.sprite[0].chroma);
    // ft_printf("C\n");
	// ft_printf("minimap in\n");
	// ft_printf("2dray out\n");
	return (0);
}
