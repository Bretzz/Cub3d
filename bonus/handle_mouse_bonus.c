/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:29:54 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/29 20:36:37 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	handle_mouse(int keysym, int x, int y, t_mlx *mlx)
{
	char	buffer[MSG_LEN + 6];
	float	ray;

	(void)x;
	(void)y;
	if (keysym == 1)
	{
		ft_printf("PIU-PIU!!!\n");
		//player_specs(mlx->player);
		buffer_player_action(mlx->lobby[*mlx->index], "fire", buffer);
		// ft_printf("send_all(%p, %s, %u)\n", mlx, buffer, ft_strlen(buffer));
		send_all(mlx, buffer, ft_strlen(buffer), 0);
		// mlx->player.sprite[0].width++;
		ray = cast_ray(mlx,
				mlx->player.pos[0],
				mlx->player.pos[1],
				mlx->player.dir[0]);
		// mlx->player.sprite[0].width--;
		float heigth = (ray / cosf(-(mlx->player.dir[1] - 90) * M_PI / 180)) * sinf(-(mlx->player.dir[1] - 90) * M_PI / 180) + 0.24f;
		printf("ray len %f, ray dir[1] %f, ray heigth %f\n", ray, -(mlx->player.dir[1] - 90), heigth);
	}
	else
		ft_printf("Mouse thing N. %d\n", keysym);
	return (0);
}
