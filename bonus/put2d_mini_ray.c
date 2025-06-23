/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2d_mini_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:40 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/23 11:50:00 by topiana-         ###   ########.fr       */
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
	if (mlx->ray.len != 0)
	{
		ray[0] = (mlx->ray.hit[0] * side);
		ray[1] = (mlx->ray.hit[1] * side);
		pos[0] = (mlx->player.pos[0] * side);
		pos[1] = (mlx->player.pos[1] * side);
		// if (ray[0] % 10 == 0 && ray[1] % 10 == 0)
		// 	ft_printf("ray is hitting [%d, %d]\n", ray[0], ray[1]);
		put_line(&mlx->img[1], pos, ray, color);
	}
	return (0);
}
