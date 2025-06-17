/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_data_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:49:51 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/17 16:04:48 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	ack_map_init(t_multi_data *data);
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
		return (0);
	get_map_stats((const char **)mlx->map.mtx,
		MLX_WIN_X, MLX_WIN_Y, mlx->map.stats);
	mlx->map.mini_side = mlx->map.stats[2] / 4;
	mlx->map.sky = 0xadd8e6;
	mlx->map.floor = 0xcaf0d5;
	get_player_stats(mlx->map.mtx, mlx->player.pos, mlx->player.dir);
	mlx->player.fov[0] = 60;
	mlx->player.fov[1] = 60;
	mlx->player.speed[0] = 0;
	mlx->player.speed[1] = 0;
	mlx->player.speed[2] = 0;
	mlx->player.tspeed[0] = 70.0f;
	mlx->player.tspeed[1] = 250;
	mlx->player.jground = 1;
	mlx->player.friction = 8;
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
	if (mlx->lobby == NULL)
		return (0);
	hpc_mutex(1);
	lbb_mutex(1);
	mlx->lobby[*mlx->index].extra = sprite_init(mlx->mlx,
			*mlx->index, 0x714333);
	mlx->player.sprite = mlx->lobby[*mlx->index].extra;
	lbb_mutex(2);
	hpc_mutex(2);
	if (mlx->lobby[*mlx->index].extra == NULL)
		return (0);
	return (1);
}

static char	*read_whole_file(char *path)
{
	char		*line;
	char		*whole_file;
	const int	fd = open(path, O_RDONLY);

	if (fd < 0)
		return (NULL);
	whole_file = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		whole_file = ft_strjoin_free(whole_file, line);
		if (whole_file == NULL)
			return (close(fd), NULL);
		line = get_next_line(fd);
	}
	return (close(fd), whole_file);
}

/* writes a file with the string passed */
static int	write_whole_file(char *whole_file)
{
	const int	fd = open("online.cub", O_WRONLY);

	if (fd < 0)
		return (1);
	if (write(fd, whole_file, ft_strlen(whole_file)) < 0)
		return (close(fd), 1);
	return (close(fd), 0);
}

int	ack_map_init(t_multi_data *data)
{
	if (data->socket == 0)
		return (1);
	if (data->index == HOST)
	{
		*ack_data() = read_whole_file(data->path);
		if (*ack_data() == NULL)
			return (0);
		ft_printf("host ack data:\n======START======\n'%s'\n======END=====\n", *ack_data());
	}
	else if (data->index == PLAYER)
	{
		if (write_whole_file(*ack_data()) != 0)
			return (0);
		ft_memset(data->path, 0, ft_strlen(data->path));
		ft_strlcpy(data->path, "online.cub", 11);
	}
	return (1);
}
