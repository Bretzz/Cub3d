/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hover.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:16:31 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/07 17:36:19 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	leave_notify_handler(t_mlx *mlx);
int	enter_notify_handler(t_mlx *mlx);

// make the cursor visible // macOS issues
int	leave_notify_handler(t_mlx *mlx)
{
	mlx->on_window = 0;
	// mlx_mouse_show(mlx->mlx, mlx->win);
	return (0);
}

// hide it again // macOS issues
int	enter_notify_handler(t_mlx *mlx)
{
	mlx->on_window = 1;
	// mlx_mouse_hide(mlx->mlx, mlx->win);
	return (0);
}
