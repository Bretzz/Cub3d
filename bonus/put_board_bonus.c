/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_board_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:56:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 23:32:11 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"


/* 0 it killed us, 1 it didn't */
static int     shoot_laser(t_mlx *mlx, float *pos, float dir, float *my_pos)
{
	const float	delta_angle = (float)mlx->player.fov[0] / mlx->win_x;       // 0 = left, pi/2 = up
	const float	kill_angle = atan2((pos[1] - my_pos[1]), (pos[0] - my_pos[0])) * 180 / M_PI;
	float    	my_dist;
	float		ray;

	// printf("dir %f, kill_angle %f, delta_angle %f\n", dir, kill_angle, delta_angle);
	if (dir < kill_angle - 10 * delta_angle
		|| dir > kill_angle + 10 * delta_angle)
	{
		ft_printf("DIRECTION OUT\n");
		return (1);
	}
	my_dist = sqrt(pow(pos[0] - my_pos[0], 2) + pow(pos[1] - my_pos[1], 2));
	ray = cast_ray(mlx, pos[0], pos[1], dir);
	ft_printf("my dist %d, ray %d\n", my_dist, ray);
	if (ray > 0 && ray < my_dist)
	{
		ft_printf("OBSTACLE OUT\n");
		return (1);
	}
	return (0);
}

/* puts all the player info, position and target (with line for shot).
if we got hit by a line (even ours) we exit. */
/* static  */int	handle_player(t_mlx *mlx, t_player *lobby, int index)
{

	if (!lbb_is_alive(lobby[index]))
		return (0);
	if (index != *mlx->index)
		put_player(mlx, (float *)mlx->lobby[index].pos, (float *)mlx->lobby[index].tar);
	// put_square(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], 10, color);
	// my_pixel_put(mlx, lobby[index].pos[0], lobby[index].pos[1], lobby[index].pos[2], color);
	if (index != *mlx->index && lobby[index].shoot == 1)
	{
		if (shoot_laser(mlx, (float *)lobby[index].pos, *(float *)&lobby[index].tar[0], (float *)mlx->player.pos) == 0)
		{
			if (*mlx->index == HOST)
			{
				char    buffer[1024];
				buffer_player_action(mlx->lobby[index], "host", buffer);
				send_all(mlx, buffer, ft_strlen(buffer), 0);
			}
			clean_exit(mlx);
		}
		lobby[index].shoot = 0;
	}
	return (1);
}


/* ! ! ! CALL BEFORE ANY OTHER PUT* ! ! ! */
int	put_board(t_mlx *mlx)
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	char			*fps;

	// ft_printf("board in\n");
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->win_x, mlx->win_y);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img
			.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.img || !mlx->img.addr)
		return (0);

	// put2d_map(mlx, mlx->map.stats[2], 0xff0000);
	// put2d_player(mlx, mlx->map.stats[2], 0x0000FF);
	// cast_field(mlx, &put2d_ray);

	// put_sky_floor(mlx);
	cast_field(mlx, &put_whole_column);
	// ft_printf("field out\n");
	put2d_minimap(mlx, 10);
	// ft_printf("minimap out\n");
	float	pos[3] = {10, 5, 3};
	put_sprite_on_map(mlx, pos, mlx->player.sprite[0]);
	
	// float	dir[2] = {0 , 90};
	// float	pos[2] = {10 , 10};
	// put_player(mlx, pos, dir);
	int	i = 0;
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(lobby[i]))
			handle_player(mlx, lobby, i);
		i++;
	}
	// ft_printf("sprite out\n");
	// cast_ray(mlx, mlx->player.pos[0], mlx->player.pos[1], mlx->player.dir[0]);
	// put2d_ray(mlx, 0xa0b000);
	// put_grid(mlx);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	
	// fps counter
	fps = ft_itoa(mlx->fps);
	if (fps == NULL)
		return (0);
	mlx_string_put(mlx->mlx, mlx->win, mlx->win_x - 25, 25, 0xff0000, fps);
	free(fps);
	// ft_printf("board out\n");
	return (1);
}
