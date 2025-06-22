/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:56:30 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 13:11:56 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	move_mouse(t_mlx *mlx)	//segfaults
{
	if (mlx->keys.arrow[0] == 1)
		mlx->player.dir[1] -= 5;
	else if (mlx->keys.arrow[1] == 1)
		mlx->player.dir[1] += 5;
	else if (mlx->keys.arrow[2] == 1)
		mlx->player.dir[0] -= 5;
	else if (mlx->keys.arrow[3] == 1)
		mlx->player.dir[0] += 5;
	return (0);
}
