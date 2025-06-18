/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:24 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 21:55:57 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	player_handle(t_mlx *mlx, t_player *fake_lobby);

/* 0 it killed us, 1 it didn't */
/* inside plot we have all the data of the sprite that is trying to kill us. */
/* NOTE: height and direction exclusion are approximative calculations :(
(accurate-ish with the bunny sprite and 1920x1080 window resolution)*/
static int	shoot_laser(t_mlx *mlx, t_plot plot, float *dir)
{
	const float	diff = fabsf(dir_diff(dir[0], plot.dir)) * MY_PI / 180;
	const float	conv_dir = -(dir[1] - 90);
	const float	laser_dir = (plot.dist * sinf(diff)) / cosf(diff);
	float		heigth;

	if ((laser_dir > (MY_PI / 20))
		|| laser_dir < -(MY_PI / 20))
		return (1);
	if (cast_ray(mlx,
			mlx->player.pos[0],
			mlx->player.pos[1],
			plot.dir) < plot.dist)
		return (1);
	heigth = (plot.dist / cosf(conv_dir * MY_PI / 180))
		* sinf(conv_dir * MY_PI / 180) + 0.5f;
	if (heigth < 0 || heigth > 0.3f)
		return (1);
	return (0);
}

/* death procedure */
static void	death_by_hand(t_mlx *mlx, int killer)
{
	char	buffer[MSG_LEN + 9];

	if (mlx->fake_index == HOST)
	{
		buffer_player_action(mlx->fake_lobby[killer],
			"host", buffer);
		send_all(mlx, buffer, ft_strlen(buffer));
	}
	clean_exit(mlx, EXIT_SUCCESS);
}

/* LOBBY MUTEX */
static void	hit_procedure(t_mlx *mlx, int index)
{
	char		buffer[MSG_LEN + 9];
	t_player	myself;

	hpc_mutex(1);
	lbb_mutex(1);
	mlx->lobby[*mlx->index].data[1]--;
	myself = mlx->lobby[*mlx->index];
	lbb_mutex(2);
	hpc_mutex(2);
	if (DEBUG)
		ft_printf("your current hp %d\n", myself.data[1]);
	if (myself.data[1] <= 0)
		death_by_hand(mlx, index);
	buffer_player_action(myself, "hit", buffer);
	send_all(mlx, buffer, ft_strlen(buffer));
}

/* puts all the player info, position and target (with line for shot).
if we got hit by a line (even ours) we exit.
'lobby' is a pointer to the head of the array. */
/* LOBBY MUTEX */
int	player_handle(t_mlx *mlx, t_player *fake_lobby)
{
	int			i;

	i = 0;
	while (i < MAXPLAYERS)
	{
		if (i == mlx->fake_index && ++i)
			continue ;
		pos_get_data(mlx, (float *)fake_lobby[i].pos, i);
		if (fake_lobby[i].data[0] == 4)
		{
			if (shoot_laser(mlx, mlx->pos_data[i],
					(float *)fake_lobby[i].tar) == 0)
				hit_procedure(mlx, i);
			lbb_mutex(1);
			mlx->lobby[i].data[0] = 0;
			lbb_mutex(2);
		}
		if (mlx->pos_data[i].seen != 0)
			mlx->fake_lobby[i].data[2] = 1;
		else
			mlx->fake_lobby[i].data[2] = 0;
		i++;
	}
	return (1);
}

// else if (!lbb_is_alive(fake_lobby[i])
// 	|| fake_lobby[i].extra == NULL)
// 	;
// if (fake_lobby[i].data[0] == 0)
// 		put_player(mlx, fake_lobby[i], 0);
// if (shootframes[i] < SHOT_FRAMES && ++shootframes[i])
// 			put_player(mlx, fake_lobby[i], 4);
// if (shootframes[i] == SHOT_FRAMES)
// {
// 	lbb_mutex(1);
// 	mlx->lobby[i].data[0] = 0;
// 	lbb_mutex(2);
// 	shootframes[i] = 0;
// }
