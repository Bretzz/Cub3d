/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_data_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:49:51 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 18:35:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	base_data_init(t_mlx *mlx, t_multi_data *data);
int	data_init(t_mlx *mlx, t_multi_data *data);
int	sprite_data_init(t_mlx *mlx);

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
int	data_init(t_mlx *mlx, t_multi_data *data)
{
	if (!juice_the_pc(mlx, data->mlx_ptr, data->win_ptr))
		return (0);
	mlx->map.mtx = map_padding(mlx->map.mtx);
	if (mlx->map.mtx == NULL)
		return (1);
	if (load_walls_texture(mlx))
	{
		ft_printfd(STDERR_FILENO, "Error: Walls texture init\n");
		return (1);
	}
	get_map_stats((const char **)mlx->map.mtx,
		MLX_WIN_X, MLX_WIN_Y, mlx->map.stats);
	mlx->map.mini_side = mlx->map.stats[2] / 4;
	get_player_stats(mlx->map.mtx, mlx->player.pos, mlx->player.dir);
	mlx->player.fov[0] = 60;
	mlx->player.fov[1] = 60;
	mlx->player.tspeed[0] = 70.0f;
	mlx->player.tspeed[1] = 250;
	mlx->player.jground = 1;
	mlx->player.friction = 8;
	mlx->frames = 1;
	mlx->keys.minimap = 1;
	yft_is_better("yft/fonts/wobbly.yft");
	return (1);
}

int	sprite_data_init(t_mlx *mlx)
{
	hpc_mutex(1);
	lbb_mutex(1);
	mlx->lobby[*mlx->index].extra = sprite_init(mlx->mlx,
			*mlx->index, 0x714333);
	mlx->fake_lobby[mlx->fake_index].extra = mlx->lobby[*mlx->index].extra;
	mlx->player.sprite = mlx->lobby[*mlx->index].extra;
	lbb_mutex(2);
	hpc_mutex(2);
	if (mlx->player.sprite == NULL)
	{
		ft_printfd(STDERR_FILENO, "Error: Player texture init\n");
		return (0);
	}
	return (1);
}

int	base_data_init(t_mlx *mlx, t_multi_data *data)
{
	mlx->map.sky = UINT_MAX;
	mlx->map.floor = UINT_MAX;
	mlx->online = 1;
	mlx->index = &data->index;
	mlx->socket = &data->socket;
	mlx->thread = data->thread;
	mlx->lobby = lbb_get_ptr(NULL);
	if (mlx->lobby == NULL)
		return (0);
	hpc_mutex(1);
	if (!ft_strcmp("lonely", mlx->lobby->ip))
		mlx->online = 0;
	hpc_mutex(2);
	return (1);
}
