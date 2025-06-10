/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hover.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:16:31 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/10 12:56:15 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	leave_notify_handler(t_mlx *mlx);
int	enter_notify_handler(t_mlx *mlx);

// make the cursor visible // macOS issues
// mlx_mouse_show(mlx->mlx, mlx->win);
int	leave_notify_handler(t_mlx *mlx)
{
	mlx->on_window = 0;
	return (0);
}

// hide it again // macOS issues
// mlx_mouse_hide(mlx->mlx, mlx->win);
int	enter_notify_handler(t_mlx *mlx)
{
	mlx->on_window = 1;
	return (0);
}
