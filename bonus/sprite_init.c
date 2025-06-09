/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:51:28 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 13:38:42 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_sprite	*sprite_init(void *mlx_ptr, int i, unsigned int subst);

/* yoooo :) */
static int	load_player_sprites(void *mlx_ptr, t_sprite *sprite)
{
	sprite[0].image = mlx_xpm_file_to_image(mlx_ptr, "./bonus/\
sprites/stop_front.xpm", &sprite[0].width, &sprite[0].heigth);
	if (sprite[0].image == NULL)
		return (1);
	sprite[0].scale = 1;
	sprite[1].image = mlx_xpm_file_to_image(mlx_ptr, "./bonus/\
sprites/stop_back.xpm", &sprite[1].width, &sprite[1].heigth);
	if (sprite[1].image == NULL)
		return (1);
	sprite[1].scale = 1;
	sprite[2].image = mlx_xpm_file_to_image(mlx_ptr, "./bonus/\
sprites/stop_left.xpm", &sprite[2].width, &sprite[2].heigth);
	if (sprite[2].image == NULL)
		return (1);
	sprite[2].scale = 1;
	sprite[3].image = mlx_xpm_file_to_image(mlx_ptr, "./bonus/\
sprites/stop_right.xpm", &sprite[3].width, &sprite[3].heigth);
	if (sprite[3].image == NULL)
		return (1);
	sprite[3].scale = 1;
	sprite[4].image = mlx_xpm_file_to_image(mlx_ptr, "./bonus/\
sprites/shoot_front.xpm", &sprite[4].width, &sprite[4].heigth);
	if (sprite[4].image == NULL)
		return (1);
	sprite[4].scale = 1;
	return (0);
}

static void	change_sprite_chroma(t_sprite *sprite, int index,
	unsigned int subst, unsigned int chroma)
{
	int	pixel[2];

	pixel[0] = 0;
	while (pixel[0] < sprite[index].width)
	{
		pixel[1] = 0;
		while (pixel[1] < sprite[index].heigth)
		{
			if (get_pixel_color(sprite[index].image,
					pixel[0], pixel[1]) == subst)
				image_pixel_put(sprite[index].image,
					pixel[0], pixel[1], chroma);
			pixel[1]++;
		}
		pixel[0]++;
	}
}

/* allocates the array of sprites changing
the color based on the index */
t_sprite	*sprite_init(void *mlx_ptr, int i, unsigned int subst)
{
	const unsigned int	c_map[6] = {0x714333,
		0xff00fa, 0xff0000, 0x00ff00, 0x0000ff, 0xa0b0c0};
	t_sprite			*sprite;
	int					j;

	sprite = (t_sprite *)malloc(SPRITE_NUM * sizeof(t_sprite));
	if (sprite == NULL)
		return (NULL);
	ft_memset(sprite, 0, SPRITE_NUM * sizeof(t_sprite));
	load_player_sprites(mlx_ptr, sprite);
	j = 0;
	while (j < SPRITE_NUM)
	{
		change_sprite_chroma(sprite, j, subst, c_map[i % sizeof(c_map)]);
		sprite[j].chroma = c_map[i % sizeof(c_map)];
		j++;
	}
	return (sprite);
}
