/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:53:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/07 18:49:32 by topiana-         ###   ########.fr       */
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

/* if a new player arrived (or the sprite was deleted)
a new sprite is provided */
/* LOBBY MUTEX */
void	update_sprites(void *mlx_ptr, t_player *lobby)
{
	unsigned int	i;
	unsigned int	j;
	t_sprite		*extra;

	i = 0;
	while (i < MAXPLAYERS)
	{
		extra = lbb_extra_leftovers(lobby[i]);
		if (lbb_is_alive(lobby[i]) && lobby[i].extra == NULL)
		{
			lobby[i].extra = sprite_init(mlx_ptr, i, 0x714333);
			ft_printf("init sprite N.%i, chroma #%X\n", i, ((t_sprite *)lobby[i].extra)[0].chroma);
		}
		else if (extra != NULL)
		{
			// ft_printf("freeing leftover image %p\n", extra);
			j = 0;
			while (j < SPRITE_NUM)
				mlx_destroy_image(mlx_ptr, extra[j++].image);
			// print_lobby(lobby);
			free(extra);
			lobby[i].extra = NULL;
		}
		i++;
	}
}

/* NOTE: fake_lobby isn't modified trought the single frame execution.
the things that will be modified are:
	>player.pos/player.dir (cub3D/update_frame)
	>lobby[*myself].hp (cub3D/handle_player)
	>lobby[others] (online) */
int update_frame(void *arg)
{
	t_mlx *const 		mlx = (t_mlx *)arg;
	char				buffer[MSG_LEN + 6];
	static unsigned int	frame;

	if (frame++ % mlx->frames == 0)
	{
		hpc_mutex(1);
		mlx->fake_index = *mlx->index;
		lbb_mutex(1);
		update_sprites(mlx->mlx, mlx->lobby);
		// copy stuff
		if (lbb_is_alive(mlx->lobby[*mlx->index]))
		{
			ft_memcpy(mlx->lobby[*mlx->index].pos, mlx->player.pos, 3 * sizeof(int));
			ft_memcpy(mlx->lobby[*mlx->index].tar, mlx->player.dir, 3 * sizeof(int));
		}
		ft_memcpy(&mlx->fake_lobby, mlx->lobby, MAXPLAYERS * sizeof(t_player));
		// mlx->player.sprite = (t_sprite *)mlx->fake_lobby[mlx->fake_index].extra;
		lbb_mutex(2);
		hpc_mutex(2);
		// ft_memcpy(mlx->fake_lobby[mlx->fake_index].pos, mlx->player.pos, 3 * sizeof(int));
		// ft_memcpy(mlx->fake_lobby[mlx->fake_index].tar, mlx->player.dir, 3 * sizeof(int));
		// mlx->player.pos = (float *)mlx->lobby[mlx->fake_index].pos;
		// mlx->player.dir = (float *)mlx->lobby[mlx->fake_index].tar;
		if (move_player(mlx) + move_mouse(mlx))
		{
			buffer_player_action(mlx->fake_lobby[mlx->fake_index], "update", buffer);
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
