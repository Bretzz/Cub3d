/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2d_mini_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:40 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 23:42:55 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	put2d_mini_ray(void *my_struct, int side, float null2, unsigned int color);

/* side is the length of the single square unit in pixel */
int	put2d_mini_ray(void *my_struct, int side, float null2, unsigned int color)
{
	t_mlx *const	mlx = (t_mlx *)my_struct;
	int				ray[2];
	int				pos[2];

	(void)null2;
	if (mlx->player.fov[1] == 61)
		ft_printf("in... ");
	if (mlx->ray.len != 0)
	{
		ray[0] = (mlx->ray.hit[0] * side) + MINIMAP_OFFSET;
		ray[1] = (mlx->ray.hit[1] * side) + MINIMAP_OFFSET;
		pos[0] = (mlx->player.pos[0] * side) + MINIMAP_OFFSET;
		pos[1] = (mlx->player.pos[1] * side) + MINIMAP_OFFSET;
		if (mlx->player.fov[1] == 61)
		{
			put_line(mlx, pos, ray, color);
			ft_printf("OK");
		}
	}
	if (mlx->player.fov[1] == 61)
		ft_printf("\n");
	return (0);
}
