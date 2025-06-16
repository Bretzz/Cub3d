/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:53:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/11 02:13:55 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* if a new player arrived (or the sprite was deleted)
a new sprite is provided */
/* LOBBY MUTEX */
void	update_sprites(void *mlx_ptr, t_player *lobby)
{
	t_sprite		*extra;
	unsigned int	i;

	i = 0;
	while (i < MAXPLAYERS)
	{
		extra = lbb_extra_leftovers(lobby[i]);
		if (lbb_is_alive(lobby[i]) && lobby[i].extra == NULL)
		{
			lobby[i].extra = sprite_init(mlx_ptr, i, 0x714333);
			if (DEBUG && lobby[i].extra)
				ft_printf("init sprite N.%i, \
chroma #%X\n", i, ((t_sprite *)lobby[i].extra)[0].chroma);
		}
		else if (extra != NULL)
		{
			sprite_destroy(mlx_ptr, extra);
			lobby[i].extra = NULL;
		}
		i++;
	}
}

/* updates the fake->lobby for new changes made
by the 'online' thread.
updates the player's slot in mlx->lobby for the
player's movement. */
static int	update_lobby(t_mlx *mlx)
{
	hpc_mutex(1);
	mlx->fake_index = *mlx->index;
	lbb_mutex(1);
	update_sprites(mlx->mlx, mlx->lobby);
	if (lbb_is_alive(mlx->lobby[*mlx->index]))
	{
		ft_memcpy(mlx->lobby[*mlx->index].pos,
			mlx->player.pos, 3 * sizeof(int));
		ft_memcpy(mlx->lobby[*mlx->index].tar,
			mlx->player.dir, 3 * sizeof(int));
	}
	ft_memcpy(mlx->fake_lobby, mlx->lobby, MAXPLAYERS * sizeof(t_player));
	lbb_mutex(2);
	hpc_mutex(2);
	return (0);
}

/* NOTE: fake_lobby isn't modified trought the single frame execution.
the things that will be modified are:
	>player.pos/player.dir (cub3D/update_frame)
	>lobby[*myself].hp (cub3D/handle_player)
	>lobby[others] (online) */
int	update_frame(void *arg)
{
	t_mlx *const		mlx = (t_mlx *)arg;
	char				buffer[MSG_LEN + 9];
	static unsigned int	frame;

	if (frame++ % mlx->frames == 0)
	{
		update_lobby(mlx);
		if (move_player(mlx) + move_mouse(mlx))
		{
			buffer_player_action(mlx->fake_lobby[mlx->fake_index],
				"update", buffer);
			send_all(mlx, buffer, ft_strlen(buffer));
		}
		mlx->player.dir[0] = normalize_dir(mlx->player.dir[0]);
		mlx->player.dir[1] = normalize_dir(mlx->player.dir[1]);
		if (!put_board(mlx))
			resign_exit(mlx);
	}
	if (frame % (75) == 0)
		mlx->fps = get_fps(frame / mlx->frames);
	return (0);
}
