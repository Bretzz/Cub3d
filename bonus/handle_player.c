/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:24 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/30 00:07:32 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

# define SHOT_FRAMES 10

int	handle_player(t_mlx *mlx, t_player *lobby, int index);

/* 0 it killed us, 1 it didn't */
static int     shoot_laser(t_mlx *mlx, float *pos, float *dir, t_plot plot)
{
	const float	*my_pos = mlx->player.pos;
	const float	kill_angle = atan2((pos[1] - my_pos[1]), (pos[0] - my_pos[0])) * 180 / M_PI;
	const float	diff = fabsf(dir_diff(dir[0], kill_angle)) * M_PI / 180;
	const float	conv_dir = -(dir[1] - 90);
	float 		heigth;

	if ((plot.dist * sinf(diff)) / cosf(diff) > (M_PI / 26))
	{
		ft_printf("DIRECTION OUT ! ! ! REVIEW ! ! !\n");
		return (1);
	}
	
	heigth = (plot.dist / cosf(conv_dir * M_PI / 180)) * sinf(conv_dir * M_PI / 180) + 0.25f;
	// printf("heigth %f\n", heigth);
	if (heigth < 0/* -0.1f */ || heigth > 0.15f)
	{
		ft_printf("HEIGTH OUT\n");
		return (1);
	}
	return (0);
}

/* death procedure */
static void	death_by_hand(t_mlx *mlx, int killer)
{
	char        buffer[MSG_LEN + 6];

	if (*mlx->index == HOST)
	{
		buffer_player_action(mlx->lobby[killer], "host", buffer);
		send_all(mlx, buffer, ft_strlen(buffer), 0);
	}
	clean_exit(mlx);
}

/* puts all the player info, position and target (with line for shot).
if we got hit by a line (even ours) we exit.
'lobby' is a pointer to the head of the array. */
int	handle_player(t_mlx *mlx, t_player *lobby, int index)
{
	char        buffer[MSG_LEN + 6];
	static int  shootframes[MAXPLAYERS];

	if (!lbb_is_alive(lobby[index]))
		return (0);
	// put_square(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], 10, color);
	// my_pixel_put(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], color);
	if (index != *mlx->index)
	{
		if (lobby[index].shoot == 0)
			put_player(mlx, lobby[index], 0, index);
		else
		{
			if (shootframes[index] < SHOT_FRAMES)
			{
				put_player(mlx, lobby[index], 4, index);
				shootframes[index]++;
			}
			if (shootframes[index] == 1 && shoot_laser(mlx, (float *)lobby[index].pos, (float *)lobby[index].tar, mlx->player.sprite_data) == 0)
			{
				lobby[*mlx->index].hp--;
				ft_printf("your current hp %d\n", lobby[*mlx->index].hp);
				if (lobby[*mlx->index].hp <= 0)
					death_by_hand(mlx, index);
				buffer_player_action(lobby[*mlx->index], "hit", buffer);
				send_all(mlx, buffer, ft_strlen(buffer), 0);
			}
			if (shootframes[index] == SHOT_FRAMES)
			{
				lobby[index].shoot = 0;
				shootframes[index] = 0;
			}
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