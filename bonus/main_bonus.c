/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:43:40 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/29 23:34:18 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* send messages trough the mlx->socket */
void    send_all(t_mlx *mlx, char *msg, size_t size, char flag)
{
	if (*mlx->socket <= 2)
		return ;
	if (flag == -1)
	{
		if (*mlx->index == HOST)
			server_sender(*mlx->socket, msg, NULL, flag);   //destroy mutex
		else
			client_sender(flag, msg, size);                                 // destroy mutex
	}
	else
	{
		if (*mlx->index == HOST)
			server_sender(*mlx->socket, msg, NULL, 0);
		else
			client_sender(*mlx->socket, msg, size);
	}
}

/* yoooo :) */
static int	load_player_sprites(t_mlx *mlx)
{
	// ugly sprite loading
	mlx->player.sprite[0].image = mlx_xpm_file_to_image(mlx->mlx, "./bonus/sprites/stop_front.xpm", &mlx->player.sprite[0].width, &mlx->player.sprite[0].heigth);
	if (mlx->player.sprite[0].image == NULL)
		return (1);
	ft_printf("front OK\n");
	mlx->player.sprite[0].scale = 1;
	mlx->player.sprite[1].image = mlx_xpm_file_to_image(mlx->mlx, "./bonus/sprites/stop_back.xpm", &mlx->player.sprite[1].width, &mlx->player.sprite[1].heigth);
	if (mlx->player.sprite[1].image == NULL)
		return (1);
	mlx->player.sprite[1].scale = 1;
	mlx->player.sprite[2].image = mlx_xpm_file_to_image(mlx->mlx, "./bonus/sprites/stop_left.xpm", &mlx->player.sprite[2].width, &mlx->player.sprite[2].heigth);
	if (mlx->player.sprite[2].image == NULL)
		return (1);
	mlx->player.sprite[2].scale = 1;
	mlx->player.sprite[3].image = mlx_xpm_file_to_image(mlx->mlx, "./bonus/sprites/stop_right.xpm", &mlx->player.sprite[3].width, &mlx->player.sprite[3].heigth);
	if (mlx->player.sprite[3].image == NULL)
		return (1);
	mlx->player.sprite[3].scale = 1;
	mlx->player.sprite[4].image = mlx_xpm_file_to_image(mlx->mlx, "./bonus/sprites/shoot_front.xpm", &mlx->player.sprite[4].width, &mlx->player.sprite[4].heigth);
	if (mlx->player.sprite[4].image == NULL)
		return (1);
	mlx->player.sprite[4].scale = 1;
	ft_printf("got sprite of size:\n\t[%d,%d]\n\t[%d,%d]\n\t[%d,%d]\n\t[%d,%d]\n\t[%d,%d]\n",
		mlx->player.sprite[0].width, mlx->player.sprite[0].heigth,
		mlx->player.sprite[1].width, mlx->player.sprite[1].heigth,
		mlx->player.sprite[2].width, mlx->player.sprite[2].heigth,
		mlx->player.sprite[3].width, mlx->player.sprite[3].heigth,
		mlx->player.sprite[4].width, mlx->player.sprite[4].heigth);
	return (0);
}

/*set up the pc-side of the t_data (mlx) struct
RETURNS: 0 all good, 1 error*/
static int	juice_the_pc(t_mlx *mlx)
{
	// mlx->mlx = mlx_init();
	// if (!mlx->mlx)
	// 	return (1);
	mlx->win_x = MLX_WIN_X;
	mlx->win_y = MLX_WIN_Y;
	// mlx->win = mlx_new_window(mlx->mlx, MLX_WIN_X, MLX_WIN_Y, "cub3d");
	// if (!mlx->win)
	// {
	// 	free(mlx->mlx);
	// 	return (1);
	// }
	return (0);
}

static int	data_init(t_mlx *mlx, char *path)
{
	/* (void)argc;(void)argv; */
	mlx->player.fov[0] = 60;
	mlx->player.fov[1] = 60;
	mlx->player.speed[0] = 0;
	mlx->player.speed[1] = 0;
	mlx->player.speed[2] = 0;
	mlx->player.tspeed[0] = 30.0f;
	mlx->player.tspeed[1] = 300;
	mlx->player.jground = 1;
	mlx->player.friction = 42;
	mlx->map.mtx = parsing(path, mlx);
	if (mlx->map.mtx == NULL)
		//return (1);
		clean_exit(mlx);
	get_map_stats((const char **)mlx->map.mtx, mlx->win_x, mlx->win_y, mlx->map.stats);
	mlx->map.sky = 0xadd8e6;
	mlx->map.floor = 0xcaf0d5;
	mlx->frames = 1;	// do not insert a multiple of 10
	// ft_printf("init frames %d\n", mlx->frames);
	// ugly sprite loading
	if (juice_the_pc(mlx) || load_player_sprites(mlx))
		return (1);
	return (0);	
}

static int cub3d_bonus(int *index, int *socket, void *thread, char *path, void *mlx_str, void *mlx_win)
{
	t_mlx	mlx;

	ft_memset(&mlx, 0, sizeof(t_mlx));
	mlx.mlx = mlx_str;
	mlx.win = mlx_win;
	if (data_init(&mlx, path))
		clean_exit(&mlx);
	
	/* ONLINE INIT */
	mlx.index = index;
	mlx.socket = socket;
	mlx.thread = thread;

	/* LOBBY INIT */
	mlx.lobby = lbb_get_ptr(NULL);
	mlx.player.pos = (float *)mlx.lobby[*mlx.index].pos;
	mlx.player.dir = (float *)mlx.lobby[*mlx.index].tar;
	get_player_stats(mlx.map.mtx, mlx.player.pos, mlx.player.dir);
	
	printf("pos %p, dir %p\n", mlx.player.pos, mlx.player.dir);
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

/* checks if the enviroment contains NAME, LOCAL_IP, SERVER_IP */
static int	env_has_vars(char *envp[])
{
	char			found[3];
	unsigned int	i;

	if (envp == NULL)
		return (0);
	ft_memset(found, 0, 3 * sizeof(char));
	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp("NAME=", envp[i], 5))
			found[0] = 1;
		else if (!ft_strncmp("SERVER_IP=", envp[i], 10))
			found[1] = 1;
		else if (!ft_strncmp("LOCAL_IP=", envp[i], 9))
			found[2] = 1;
		i++;
	}
	if (found[0] && found[1] && found[2])
		return (1);
	return (0);
}


int main(int argc, char *argv[], char *envp[])
{
	// (void)argc; (void)argv; (void)envp;
	// ft_printf("argc=%d\n", argc);
	// ft_printf("\nargv[1] %s\nargv[2] %s\nargv[3] %s\n", argv[1], argv[2], argv[3]);

	if (argc < 2 || argc > 4)
	{
		error_msg(ERR_ARGS);
		return (1);
	}
	if (argc > 2)
	{
		if (!env_has_vars(envp))
		{
			error_msg(ERR_ENVP);
			return (1);
		}
		XInitThreads();  // Must be called before any X11 functions
		if (!is_ip(argv[2]) && ft_strcmp("host", argv[2]))
		{
			ft_printf("wrong IP\n");
			return (1);
		}
		make_him_host(argv[2], envp);
		if (argc > 3)
			set_my_name(argv[3], envp);
		else
			set_my_name("b4llbre4k3r", envp);
	}
	int	i = 0;
	ft_printf("\n%s[...] ...\n", PURPLE);
	while (envp[i] != NULL)
	{
		if (!ft_strncmp("NAME=", envp[i], 5)
			|| !ft_strncmp("SERVER_IP=", envp[i], 10)
			|| !ft_strncmp("LOCAL_IP=", envp[i], 9))
			ft_printf("[%i] %s\n", i, envp[i]);
		i++;
	}
	ft_printf(RESET"\n");

	/* ONLINE */

	if (lbb_init() == NULL)
		return (1);

	void		*mlx_str = mlx_init();
	void		*mlx_win = mlx_new_window(mlx_str, MLX_WIN_X, MLX_WIN_Y, argv[3]);
	int			index = 0;
	int			socket = 0;
	pthread_t	thread = 0;

	if (argc > 2)
	{
		thread = get_me_online(&index, &socket, envp);
		if (thread == 0)
		{
			error_msg(ERR_ONLINE);
			lbb_delete_lobby(lbb_get_ptr(NULL));
			return (1);
		}
	}

	// dummy player
	// const char msg[] = "dummy:0.0.0.0:1089470464_1085276160_1065353216:1127481344_1119092736_0";
	// t_player *lobby = lbb_get_ptr(NULL);
	// ft_strlcpy(lobby[2].name, "dummy", 10);
	// ft_strlcpy(lobby[2].name, "0.0.0.0", 10);
	// lobby[2].pos[0] = 1090701466;
	// lobby[2].pos[1] = 1085620093;
	// lobby[2].pos[2] = 1065353216;
	// lobby[2].tar[0] = 1095720131;
	// lobby[2].tar[0] = 1120141309;
	// lobby[2].tar[0] = 0;
	// lobby[2].hp = PLAYER_HP;

	// usleep(1000);
	// ft_printf("SERVER_IP=%s, NAME=%s\n", get_serv_ip(envp), get_my_name(envp));
	// ft_printf(ERROR"get_me_online couses the invalid read and the map to vanish!%s\n", RESET);
	cub3d_bonus(&index, &socket, &thread, argv[1], mlx_str, mlx_win);
	return (0);
}
