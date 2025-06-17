/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:01:44 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/17 17:55:47 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* send messages trough the mlx->socket */
/* NOTE: no hpc_mutex of lbb_mutex locked going in this */
void	send_all(t_mlx *mlx, char *msg, size_t size)
{
	if (!mlx->index || !mlx->socket || *mlx->socket <= 2)
		return ;
	if (*mlx->index == HOST)
		server_sender(*mlx->socket, msg, NULL, 0);
	else
		client_sender(*mlx->socket, msg, size);
}
