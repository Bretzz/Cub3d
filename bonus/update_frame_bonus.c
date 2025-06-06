/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:53:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/06 15:51:19 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include <sys/time.h>

#include <stdio.h>

static int	get_fps(int frame)
{
	static struct timeval	old_time;
	static int				old_frame;
	int						fps;
	struct timeval			now_time;

	if (old_frame == 0)
	{
		gettimeofday(&old_time, NULL);
		old_frame = frame;
		return (0);
	}
	gettimeofday(&now_time, NULL);
	double time = (double)(((now_time.tv_sec * 1000000 + now_time.tv_usec) - (old_time.tv_sec * 1000000 + old_time.tv_usec))) / 1000000;
	fps = (frame - old_frame) / time;
	old_time = now_time;
	old_frame = frame;
	return (fps);
}

/* yoooo :) */
static int	load_player_sprites(void *mlx_ptr, t_sprite *sprite)
{
	// ugly sprite loading
	sprite[0].image = mlx_xpm_file_to_image(mlx_ptr, "./bonus/sprites/stop_front.xpm", &sprite[0].width, &sprite[0].heigth);
	if (sprite[0].image == NULL)
		return (1);
	sprite[0].scale = 1;
	sprite[1].image = mlx_xpm_file_to_image(mlx_ptr, "./bonus/sprites/stop_back.xpm", &sprite[1].width, &sprite[1].heigth);
	if (sprite[1].image == NULL)
		return (1);
	sprite[1].scale = 1;
	sprite[2].image = mlx_xpm_file_to_image(mlx_ptr, "./bonus/sprites/stop_left.xpm", &sprite[2].width, &sprite[2].heigth);
	if (sprite[2].image == NULL)
		return (1);
	sprite[2].scale = 1;
	sprite[3].image = mlx_xpm_file_to_image(mlx_ptr, "./bonus/sprites/stop_right.xpm", &sprite[3].width, &sprite[3].heigth);
	if (sprite[3].image == NULL)
		return (1);
	sprite[3].scale = 1;
	sprite[4].image = mlx_xpm_file_to_image(mlx_ptr, "./bonus/sprites/shoot_front.xpm", &sprite[4].width, &sprite[4].heigth);
	if (sprite[4].image == NULL)
		return (1);
	sprite[4].scale = 1;
	ft_printf("got sprite of size:\n\t[%d,%d]\n\t[%d,%d]\n\t[%d,%d]\n\t[%d,%d]\n\t[%d,%d]\n",
		sprite[0].width, sprite[0].heigth,
		sprite[1].width, sprite[1].heigth,
		sprite[2].width, sprite[2].heigth,
		sprite[3].width, sprite[3].heigth,
		sprite[4].width, sprite[4].heigth);
	return (0);
}

/* allocates the array of sprites changing
the color based on the index */
static t_sprite *sprite_init(void *mlx_ptr, int i, unsigned int subst)
{
	const unsigned int	c_map[6] = { 0x714333, 0xff00fa, 0xff0000, 0x00ff00, 0x0000ff, 0xa0b0c0};
	t_sprite 			*sprite;
	int					pixel[2];
	int					j;

	sprite = (t_sprite *)malloc(SPRITE_NUM * sizeof(t_sprite));
	if (sprite == NULL)
		return (NULL);
	ft_memset(sprite, 0, SPRITE_NUM * sizeof(t_sprite));
	load_player_sprites(mlx_ptr, sprite);
	j = 0;
	while (j < SPRITE_NUM)
	{
		pixel[0] = 0;
		while (pixel[0] < sprite[j].width)
		{
			pixel[1] = 0;
			while (pixel[1] < sprite[j].heigth)
			{
				if (get_pixel_color(sprite[j].image, pixel[0], pixel[1]) == subst)
					image_pixel_put(sprite[j].image, pixel[0], pixel[1], c_map[i % 6]);
				pixel[1]++;
			}
			pixel[0]++;
		}
		sprite[j].chroma = c_map[i % 6];
		j++;
	}
	return (sprite);
}

/* if a new player arrived (or the sprite was deleted)
a new sprite is provided */
/* LOBBY MUTEX */
void	update_sprites(void *mlx_ptr, t_player *lobby)
{
	unsigned int	i;

	i = 0;
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(lobby[i]) && lobby[i].extra == NULL)
		{
			lobby[i].extra = sprite_init(mlx_ptr, i, 0x714333);
			ft_printf("init sprite N.%i, chroma #%X\n", i, ((t_sprite *)lobby[i].extra)[0].chroma);
		}
		i++;
	}
}

/* NOTE: fake_lobby isn't modified trought the single frame execution.
the things that will be modified are:
	>player.pos/player.dir (cub3D)
	>lobby[*myself].hp (cub3D)
	>lobby[others] (online) */
int update_frame(void *arg)
{
	t_mlx *const 		mlx = (t_mlx *)arg;
	char				buffer[MSG_LEN + 6];
	static unsigned int	frame;

	if (frame++ % mlx->frames == 0)
	{
		lbb_mutex(1);
		update_sprites(mlx->mlx, mlx->lobby);
		ft_memcpy(mlx->lobby[*mlx->index].pos, mlx->player.pos, 3 * sizeof(int));
		ft_memcpy(mlx->lobby[*mlx->index].tar, mlx->player.dir, 3 * sizeof(int));
		ft_memcpy(&mlx->fake_lobby, mlx->lobby, MAXPLAYERS * sizeof(t_player));
		lbb_mutex(2);
		// ft_memcpy(mlx->fake_lobby[*mlx->index].pos, mlx->player.pos, 3 * sizeof(int));
		// ft_memcpy(mlx->fake_lobby[*mlx->index].tar, mlx->player.dir, 3 * sizeof(int));
		// mlx->player.pos = (float *)mlx->lobby[*mlx->index].pos;
		// mlx->player.dir = (float *)mlx->lobby[*mlx->index].tar;
		mlx->player.sprite = (t_sprite *)mlx->fake_lobby[*mlx->index].extra;
		if (move_player(mlx) + move_mouse(mlx))
		{
			buffer_player_action(mlx->fake_lobby[*mlx->index], "update", buffer);
			send_all(mlx, buffer, ft_strlen(buffer));
		}
		// move_mouse(mlx);
		mlx->player.dir[0] = normalize_dir(mlx->player.dir[0]);
		mlx->player.dir[1] = normalize_dir(mlx->player.dir[1]);
		put_board(mlx);
	}
	else
		usleep(1000);
	if (frame % (75) == 0) 
		mlx->fps = get_fps(frame / mlx->frames);
	// if (*mlx->socket > 2 && frame % (3000) == 0) 
	// 	print_lobby(mlx->fake_lobby);
	return (0);
}
