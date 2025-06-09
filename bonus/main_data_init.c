/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_data_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:49:51 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 14:41:01 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	data_init(t_mlx *mlx, char *path, void *mlx_ptr, void *win_ptr);
int	online_data_init(t_mlx *mlx,
		int *index, int *socket, unsigned long thread);

/* assign the variables, if we are 'online' so mlx is initialized,
or initializes the mlx struct and window.
RETURNS: 1 ok, 0 error. */
static int	juice_the_pc(t_mlx *mlx, void *mlx_ptr, void *win_ptr)
{
	if (mlx_ptr)
		mlx->mlx = mlx_ptr;
	else
		mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		return (0);
	if (win_ptr)
		mlx->win = win_ptr;
	else
		mlx->win = mlx_new_window(mlx->mlx, MLX_WIN_X, MLX_WIN_Y, "cub3D");
	if (mlx->win == NULL)
		return (free(mlx->mlx), 0);
	return (1);
}

/* initializes all the struct's data.
RETURNS: 1 ok, 0 error. */
int	data_init(t_mlx *mlx, char *path, void *mlx_ptr, void *win_ptr)
{
	ft_memset(mlx, 0, sizeof(t_mlx));
	mlx->map.mtx = parsing(path, mlx);
	if (mlx->map.mtx == NULL)
		clean_exit(mlx);
	get_map_stats((const char **)mlx->map.mtx,
		MLX_WIN_X, MLX_WIN_Y, mlx->map.stats);
	mlx->map.sky = 0xadd8e6;
	mlx->map.floor = 0xcaf0d5;
	get_player_stats(mlx->map.mtx, mlx->player.pos, mlx->player.dir);
	mlx->player.fov[0] = 60;
	mlx->player.fov[1] = 60;
	mlx->player.speed[0] = 0;
	mlx->player.speed[1] = 0;
	mlx->player.speed[2] = 0;
	mlx->player.tspeed[0] = 30.0f;
	mlx->player.tspeed[1] = 300;
	mlx->player.jground = 1;
	mlx->player.friction = 42;
	mlx->frames = 1;
	if (!juice_the_pc(mlx, mlx_ptr, win_ptr))
		return (0);
	return (1);
}

int	online_data_init(t_mlx *mlx,
	int *index, int *socket, unsigned long thread)
{
	mlx->index = index;
	mlx->socket = socket;
	mlx->thread = thread;
	mlx->lobby = lbb_get_ptr(NULL);
	hpc_mutex(1);
	lbb_mutex(1);
	mlx->lobby[*mlx->index].extra = sprite_init(mlx->mlx,
			*mlx->index, 0x714333);
	mlx->player.sprite = mlx->lobby[*mlx->index].extra;
	lbb_mutex(2);
	hpc_mutex(2);
	return (1);
}
