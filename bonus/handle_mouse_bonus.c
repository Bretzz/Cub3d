/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:29:54 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 17:16:44 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	handle_mouse(int keysym, int x, int y, t_mlx *mlx)
{
	char	buffer[MSG_LEN + 9];

	(void)x;
	(void)y;
	if (keysym == 1)
	{
		if (DEBUG)
		{
			ft_printf("PIU-PIU!!!\n");
			mlx->player.dir[2]++;
			cast_ray(mlx,
				mlx->player.pos[0],
				mlx->player.pos[1],
				mlx->player.dir[0]);
			mlx->player.dir[2]--;
		}
		buffer_player_action(mlx->fake_lobby[*mlx->index], "fire", buffer);
		send_all(mlx, buffer, ft_strlen(buffer));
	}
	else if (DEBUG)
		ft_printf("Mouse thing N. %d\n", keysym);
	return (0);
}
