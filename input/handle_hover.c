/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hover.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:16:31 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 12:36:08 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	leave_notify_handler(t_mlx *mlx);
int	enter_notify_handler(t_mlx *mlx);

int	leave_notify_handler(t_mlx *mlx)
{
	mlx->on_window = 0;
	mlx_mouse_show(mlx->mlx, mlx->win); // make the cursor visible // macOS issues
	return (0);
}

int	enter_notify_handler(t_mlx *mlx)
{
	mlx->on_window = 1;
	mlx_mouse_hide(mlx->mlx, mlx->win); // hide it again // macOS issues
	return (0);
}
