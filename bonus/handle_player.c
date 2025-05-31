/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:24 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/31 16:34:45 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

# define SHOT_FRAMES 10

int	handle_player(t_mlx *mlx, t_player *lobby, int index);

/* 0 it killed us, 1 it didn't */
/* inside plot we have all the data of the sprite that is trying to kill us. */
/* LOBBY MUTEX */
static int     shoot_laser(t_mlx * mlx, t_plot plot, float *dir)
{
	const float	diff = fabsf(dir_diff(dir[0], plot.dir)) * M_PI / 180;
	const float	conv_dir = -(dir[1] - 90);
	float 		heigth;

	if ((plot.dist * sinf(diff)) / cosf(diff) > (M_PI / 26))
	{
		// ft_printf("DIRECTION OUT ! ! ! REVIEW ! ! !\n");
		return (1);
	}

	if (cast_ray(mlx, mlx->player.pos[0], mlx->player.pos[1], plot.dir) < plot.dist)
		return (1);
	// ft_printf("plot.dist %f, conv_dir %f\n", plot.dist, conv_dir);
	heigth = (plot.dist / cosf(conv_dir * M_PI / 180)) * sinf(conv_dir * M_PI / 180) + 0.25f;
	// printf("heigth %f\n", heigth);
	if (heigth < 0/* -0.1f */ || heigth > 0.15f)
	{
		// ft_printf("HEIGTH OUT\n");
		return (1);
	}
	return (0);
}

/* death procedure */
/* LOBBY MUTEX */
static void	death_by_hand(t_mlx *mlx, int killer)
{
	char        buffer[MSG_LEN + 6];
	int			my_index;

	// hpc_mutex(1);
	my_index = *mlx->index;
	// hpc_mutex(2);
	if (*mlx->index == HOST)
	{
		buffer_player_action(mlx->fake_lobby[killer], "host", buffer);
		send_all(mlx, buffer, ft_strlen(buffer));
	}
	clean_exit(mlx);
}

/* puts all the player info, position and target (with line for shot).
if we got hit by a line (even ours) we exit.
'lobby' is a pointer to the head of the array. */
/* LOBBY MUTEX */
int	handle_player(t_mlx *mlx, t_player *fake_lobby, int index)
{
	char        buffer[MSG_LEN + 6];
	static int  shootframes[MAXPLAYERS];
	t_player	myself;

	// hpc_mutex(1);
	int	my_index = *mlx->index;
	// hpc_mutex(2);
	if (!lbb_is_alive(fake_lobby[index]) || fake_lobby[index].extra == NULL)
		return (0);
	// put_square(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], 10, color);
	// my_pixel_put(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], color);
	if (index == my_index)
		return (0);
	if (fake_lobby[index].shoot == 0)
		put_player(mlx, fake_lobby[index], 0/* , index */);
	else
	{
		if (shootframes[index] < SHOT_FRAMES)
		{
			put_player(mlx, fake_lobby[index], 4/* , index */);
			shootframes[index]++;
		}
		if (shootframes[index] == 1 && mlx->player.last_sprite_data.dist != 0
			&& shoot_laser(mlx, mlx->player.last_sprite_data, (float *)fake_lobby[index].tar) == 0)
		{
			lbb_mutex(1);
			mlx->lobby[my_index].hp--;
			myself = mlx->lobby[my_index];
			lbb_mutex(2);
			ft_printf("your current hp %d\n", myself.hp);
			if (myself.hp <= 0)
				death_by_hand(mlx, index);
			buffer_player_action(myself, "hit", buffer);
			send_all(mlx, buffer, ft_strlen(buffer));
		}
		if (shootframes[index] == SHOT_FRAMES)
		{
			lbb_mutex(1);
			mlx->lobby[index].shoot = 0;
			lbb_mutex(2);
			shootframes[index] = 0;
		}
	}
	return (1);
}


// if (*mlx->index == HOST)
// {
//     buffer_player_action(lobby[index], "host", buffer);
//     send_all(mlx, buffer, ft_strlen(buffer), 0);
// }
// clean_exit(mlx);