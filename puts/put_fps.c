/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_fps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:13:41 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 13:56:05 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "puts.h"

/* welp... */
void	put_fps(t_mlx *mlx)
{
	char			*fps;

	fps = ft_itoa(mlx->fps);
	if (fps == NULL)
		return ;
	mlx_string_put(mlx->mlx, mlx->win, MLX_WIN_X - 25, 25, 0xff0000, fps);
	free(fps);
}
