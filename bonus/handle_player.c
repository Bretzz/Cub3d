/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:24 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 20:01:16 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

#define SHOT_FRAMES 10

int	handle_player(t_mlx *mlx, t_player *lobby, int index);

/* 0 it killed us, 1 it didn't */
/* inside plot we have all the data of the sprite that is trying to kill us. */
/* NOTE: height and direction exclusion are approximative calculations :(
(accurate-ish with the bunny sprite and 1920x1080 window resolution)*/
static int	shoot_laser(t_mlx *mlx, t_plot plot, float *dir)
{
	const float	diff = fabsf(dir_diff(dir[0], plot.dir)) * M_PI / 180;
	const float	conv_dir = -(dir[1] - 90);
	const float	laser_dir = (plot.dist * sinf(diff)) / cosf(diff);
	float		heigth;

	if ((laser_dir > (M_PI / 20))
		|| laser_dir < -(M_PI / 20))
		return (1);
	if (cast_ray(mlx,
			mlx->player.pos[0],
			mlx->player.pos[1],
			plot.dir) < plot.dist)
		return (1);
	heigth = (plot.dist / cosf(conv_dir * M_PI / 180))
		* sinf(conv_dir * M_PI / 180) + 0.5f;
	if (heigth < 0 || heigth > 0.3f)
		return (1);
	return (0);
}

/* death procedure */
static void	death_by_hand(t_mlx *mlx, int killer)
{
	char	buffer[MSG_LEN + 6];

	if (mlx->fake_index == HOST)
	{
		buffer_player_action(mlx->fake_lobby[killer],
			"host", buffer);
		send_all(mlx, buffer, ft_strlen(buffer));
	}
	clean_exit(mlx);
}

/* LOBBY MUTEX */
static void	hit_procedure(t_mlx *mlx, int index)
{
	char		buffer[MSG_LEN + 6];
	t_player	myself;

	hpc_mutex(1);
	lbb_mutex(1);
	mlx->lobby[*mlx->index].hp--;
	myself = mlx->lobby[*mlx->index];
	lbb_mutex(2);
	hpc_mutex(2);
	if (DEBUG)
		ft_printf("your current hp %d\n", myself.hp);
	if (myself.hp <= 0)
		death_by_hand(mlx, index);
	buffer_player_action(myself, "hit", buffer);
	send_all(mlx, buffer, ft_strlen(buffer));
}

/* puts all the player info, position and target (with line for shot).
if we got hit by a line (even ours) we exit.
'lobby' is a pointer to the head of the array. */
/* LOBBY MUTEX */
int	handle_player(t_mlx *mlx, t_player *fake_lobby, int index)
{
	static int	shootframes[MAXPLAYERS];

	if (!lbb_is_alive(fake_lobby[index]) || fake_lobby[index].extra == NULL)
		return (0);
	if (index == mlx->fake_index)
		return (0);
	if (fake_lobby[index].action == 0)
		put_player(mlx, fake_lobby[index], 0);
	else
	{
		if (shootframes[index] < SHOT_FRAMES && ++shootframes[index])
			put_player(mlx, fake_lobby[index], 4);
		if (shootframes[index] == 1 && mlx->player.last_sprite_data.dist != 0
			&& shoot_laser(mlx, mlx->player.last_sprite_data,
				(float *)fake_lobby[index].tar) == 0)
			hit_procedure(mlx, index);
		if (shootframes[index] == SHOT_FRAMES)
		{
			lbb_mutex(1);
			mlx->lobby[index].action = 0;
			lbb_mutex(2);
			shootframes[index] = 0;
		}
	}
	return (1);
}
