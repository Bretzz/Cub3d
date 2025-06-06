/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:43:40 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/06 18:38:07 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"


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
static int	data_init(t_mlx *mlx, char *path, void *mlx_ptr, void *win_ptr)
{
	/* (void)argc;(void)argv; */
	ft_memset(mlx, 0, sizeof(t_mlx));
	// map init
	mlx->map.mtx = parsing(path, mlx);
	if (mlx->map.mtx == NULL)
		clean_exit(mlx);
	get_map_stats((const char **)mlx->map.mtx, MLX_WIN_X, MLX_WIN_Y, mlx->map.stats);
	mlx->map.sky = 0xadd8e6;
	mlx->map.floor = 0xcaf0d5;
	// player init
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
	mlx->frames = 1;	// do not insert a multiple of 10
	if (!juice_the_pc(mlx, mlx_ptr, win_ptr))
		return (0);
	return (1);	
}

static int online_data_init(t_mlx *mlx, int *index, int *socket, unsigned long thread)
{
	/* ONLINE INIT */
	mlx->index = index;
	mlx->socket = socket;
	mlx->thread = thread;
	/* LOBBY INIT */
	mlx->lobby = lbb_get_ptr(NULL);\
	return (1);
}

static int cub3d_bonus(t_multi_data *data)
{
	t_mlx	mlx;

	if (!data_init(&mlx, data->path, data->mlx_ptr, data->win_ptr)
		|| !online_data_init(&mlx, &data->index, &data->socket, data->thread))
		clean_exit(&mlx);
		
	printf("player [%f, %f, %f] looking [%f, %f]\n", mlx.player.pos[0], mlx.player.pos[1], mlx.player.pos[2], mlx.player.dir[0], mlx.player.dir[1]);
	// print_lobby(lbb_get_ptr(NULL));
	ft_printf(RED"MLX ADDR: %p, index %d, socket %d%s\n", &mlx, *mlx.index, *mlx.socket, RESET);

	// key hooks
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &handle_key_press, &mlx);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, &handle_key_release, &mlx);

	// mouse hook
	mlx_mouse_hook(mlx.win, &handle_mouse, &mlx);

	// on window hooks
	mlx_hook(mlx.win, EnterNotify, (1L << 4), &enter_notify_handler, &mlx);
	mlx_hook(mlx.win, LeaveNotify, (1L << 5), &leave_notify_handler, &mlx);

	// red cross
	mlx_hook(mlx.win, DestroyNotify, StructureNotifyMask, &clean_exit, &mlx);

	// ft_printf("frames after init %d\n", mlx.frames);

	// frame updater
	mlx_loop_hook(mlx.mlx, &update_frame, &mlx);

	ft_printf("\n! ! ! CHECK WHY IT GET STUCK IN CORNERS SOMETIMES ! ! !\n! ! ! CHECK OUTER CORNERS OF ISOLATED CUB3s SOMETIMES SEE TROUGH ! ! !\nTO-DO: CHANGE SPEED TO INT (DONE)\nSOMETIMES CRASHES NEAR THE BIG ORIZON (DONE-ish)\n\t%sADD CHROMAS FOR DIFFERENT PLAYERS%s\n", BOLD, RESET);

	mlx_loop(mlx.mlx);
	return (0);
}

/* 0 ok, 1 error */
int	online_setup(t_multi_data *data, int argc, char *argv[], char *envp[])
{
	char	**fenv;

	if (!is_ip(argv[2]) && ft_strcmp("host", argv[2]))
	{
		error_msg(ERR_IP_FORMAT);
		return (1);
	}
	fenv = fake_env_init(envp);
	if (fenv == NULL)
	{
		error_msg(ERR_MALLOC);
		return (1);
	}
	/* DATA SETUP */
	make_him_host(argv[2], fenv);
	if (argc > 3)
		set_my_name(argv[3], fenv);
	else
		set_my_name("b4llbre4k3r", fenv);

	/* DATA CHECK */
	int	i = 0;
	ft_printf("\n%s[...] ...\n", PURPLE);
	while (fenv[i] != NULL)
	{
		if (!ft_strncmp("NAME=", fenv[i], 5)
			|| !ft_strncmp("SERVER_IP=", fenv[i], 10)
			|| !ft_strncmp("LOCAL_IP=", fenv[i], 9))
			ft_printf("[%i] %s\n", i, fenv[i]);
		i++;
	}
	ft_printf(RESET"\n");
	
	// if (lbb_init() == NULL)
	// 	return (1);
	// lbb_mutex(0);	// mutex init

	XInitThreads();  // Must be called before any X11 functions
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (free_fake_env(fenv), 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, MLX_WIN_X, MLX_WIN_Y, "cub3D");
	if (data->win_ptr == NULL)
		return (mlx_destroy_display(data->mlx_ptr), free_fake_env(fenv), 1);
	data->index = 0;
	data->socket = 0;
	data->thread = 0;
	data->path = argv[1];
	
	/* ONLINE */
	if (hpc_init() == 1)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);	// macOS issues
		free(data->mlx_ptr);
		free_fake_env(fenv);
		return (1);
	}
	
	data->thread = get_me_online(&data->index, &data->socket, fenv);
	if (data->thread == 0)
	{
		error_msg(ERR_ONLINE);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);	// macOS issues
		free(data->mlx_ptr);
		hpc_free(&data->socket, &data->index, data->thread);
		free_fake_env(fenv);
		return (1);
	}
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	t_multi_data	data;

	// (void)argc; (void)argv; (void)envp;
	// ft_printf("argc=%d\n", argc);
	// ft_printf("\nargv[1] %s\nargv[2] %s\nargv[3] %s\n", argv[1], argv[2], argv[3]);

	if (argc < 2 || argc > 4)
	{
		error_msg(ERR_ARGS);
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_multi_data));
	if (argc == 2)
	{
		data.path = argv[1];
		if (lbb_init() == NULL)
			return (1);
		ft_strlcpy(((t_player *)lbb_get_ptr(NULL))[HOST].name, "cub3D", 42);
		ft_strlcpy(((t_player *)lbb_get_ptr(NULL))[HOST].ip, "local", 15);
	}
	if (argc > 2)
	{
		if (online_setup(&data, argc, argv, envp) == 1)
			return (1);
	}
	// 	fenv = fake_env_init(envp);
	// 	if (fenv == NULL)
	// 	{
	// 		error_msg(ERR_MALLOC);
	// 		return (1);
	// 	}
	// 	if (!env_has_vars(fenv))
	// 	{
	// 		error_msg(ERR_ENVP);
	// 		return (free_fake_env(fenv), 1);
	// 	}
	// 	XInitThreads();  // Must be called before any X11 functions
	// 	if (!is_ip(argv[2]) && ft_strcmp("host", argv[2]))
	// 	{
	// 		ft_printf("wrong IP\n");
	// 		return (free_fake_env(fenv), 1);
	// 	}
	// 	make_him_host(argv[2], fenv);
	// 	if (argc > 3)
	// 		set_my_name(argv[3], fenv);
	// 	else
	// 		set_my_name("b4llbre4k3r", fenv);
	// 	int	i = 0;
	// 	ft_printf("\n%s[...] ...\n", PURPLE);
	// 	while (fenv[i] != NULL)
	// 	{
	// 		if (!ft_strncmp("NAME=", fenv[i], 5)
	// 			|| !ft_strncmp("SERVER_IP=", fenv[i], 10)
	// 			|| !ft_strncmp("LOCAL_IP=", fenv[i], 9))
	// 			ft_printf("[%i] %s\n", i, fenv[i]);
	// 		i++;
	// 	}
	// 	ft_printf(RESET"\n");
	// }

	// /* ONLINE */

	// if (argc > 2)
	// 	hpc_init();
	// else
	// 	lbb_init();

	// // if (lbb_init() == NULL)
	// // 	return (1);
	// // lbb_mutex(0);	// mutex init

	// void		*mlx_ptr = mlx_init();
	// void		*mlx_win = mlx_new_window(mlx_ptr, MLX_WIN_X, MLX_WIN_Y, "cub3D");
	// int			index = 0;
	// int			socket = 0;
	// pthread_t	thread = 0;

	// if (argc > 2)
	// {
	// 	thread = get_me_online(&index, &socket, fenv);
	// 	if (thread == 0)
	// 	{
	// 		error_msg(ERR_ONLINE);
	// 		hpc_free(&socket, &index, &thread);
	// 		free_fake_env(fenv);
	// 		return (1);
	// 	}
	// }
	// else
	// {
	// 	ft_strlcpy(((t_player *)lbb_get_ptr(NULL))[HOST].name, "cub3D", 42);
	// 	ft_strlcpy(((t_player *)lbb_get_ptr(NULL))[HOST].ip, "local", 15);
	// }

	// dummy player
	// const char msg[] = "dummy:0.0.0.0:1089470464_1085276160_1065353216:1127481344_1119092736_0";
	t_player *lobby = lbb_get_ptr(NULL);
	ft_strlcpy(lobby[2].name, "dummy", 10);
	ft_strlcpy(lobby[2].name, "0.0.0.0", 10);
	lobby[2].pos[0] = 1090701466;
	lobby[2].pos[1] = 1085620093;
	lobby[2].pos[2] = 1065353216;
	lobby[2].tar[0] = 1095720131;
	lobby[2].tar[0] = 1120141309;
	lobby[2].tar[0] = 0;
	lobby[2].hp = PLAYER_HP;

	// usleep(1000);
	// ft_printf("SERVER_IP=%s, NAME=%s\n", get_serv_ip(fenv), get_my_name(fenv));
	// ft_printf(ERROR"get_me_online couses the invalid read and the map to vanish!%s\n", RESET);
	cub3d_bonus(&data);
	return (0);
}
