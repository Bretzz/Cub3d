/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hover.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:16:31 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/26 15:42:52 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	leave_notify_handler(t_mlx *mlx);
int	enter_notify_handler(t_mlx *mlx);

// make the cursor visible // macOS issues
int	leave_notify_handler(t_mlx *mlx)
{
	mlx_mouse_show(mlx->mlx, mlx->win);
	mlx->on_window = 0;
	return (0);
}

// hide it again // macOS issues
int	enter_notify_handler(t_mlx *mlx)
{
	mlx_mouse_hide(mlx->mlx, mlx->win);
	mlx->on_window = 1;
	return (0);
}
