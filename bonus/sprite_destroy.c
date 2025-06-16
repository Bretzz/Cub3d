/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:33:27 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/10 15:40:01 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* destroys all the sprite initialized
NOTE: assuming you're passing a pointer to
an array of sprites of size SPRITE_NUM.
the pointer will be finally free'd */
void	sprite_destroy(void *mlx_ptr, t_sprite *sprite)
{
	int	j;

	j = 0;
	while (j < SPRITE_NUM)
	{
		if (sprite[j].image != NULL)
			mlx_destroy_image(mlx_ptr, sprite[j].image);
		j++;
	}
	free(sprite);
}
