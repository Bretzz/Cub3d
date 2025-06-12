/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:43:40 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/12 13:18:20 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	mini_clean_exit(t_multi_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

/*
! ! ! CRASHED THE MINIMAP ON HOST CHANGE ! ! !
! ! ! CHECK WHY IT GET STUCK IN CORNERS SOMETIMES ! ! !
! ! ! CHECK OUTER CORNERS OF ISOLATED CUB3s SOMETIMES SEE TROUGH ! ! !
TO-DO: CHANGE SPEED TO INT (DONE)
SOMETIMES CRASHES NEAR THE BIG ORIZON (DONE-ish)
ADD CHROMAS FOR DIFFERENT PLAYERS */
static int	cub3d_bonus(t_multi_data *data)
{
	t_mlx	mlx;

	if (!data_init(&mlx, data->path, data->mlx_ptr, data->win_ptr)
		|| !online_data_init(&mlx, &data->index, &data->socket, data->thread))
		clean_exit(&mlx);
	if (DEBUG)
		ft_printf(RED"MLX ADDR: %p, index %d, socket %d%s\n",
			&mlx, *mlx.index, *mlx.socket, RESET);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &handle_key_press, &mlx);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, &handle_key_release, &mlx);
	mlx_mouse_hook(mlx.win, &handle_mouse, &mlx);
	mlx_hook(mlx.win, EnterNotify, (1L << 4), &enter_notify_handler, &mlx);
	mlx_hook(mlx.win, LeaveNotify, (1L << 5), &leave_notify_handler, &mlx);
	mlx_hook(mlx.win, DestroyNotify, StructureNotifyMask, &resign_exit, &mlx);
	mlx_loop_hook(mlx.mlx, &update_frame, &mlx);
	mlx_do_sync(mlx.mlx);
	mlx_loop(mlx.mlx);
	return (0);
}

/* 0 ok, 1 error */
int	online_setup(t_multi_data *data, int argc, char *argv[])
{
	XInitThreads();
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			MLX_WIN_X, MLX_WIN_Y, "cub3D");
	if (data->win_ptr == NULL)
		return (mlx_destroy_display(data->mlx_ptr),
			free(data->mlx_ptr), 1);
	if (hpc_init() == 1)
		return (mini_clean_exit(data), 1);
	if (argc == 3)
		data->thread = (unsigned long)get_me_online(&data->index,
				&data->socket, argv[2], "b4llbre4k3r");
	else
		data->thread = (unsigned long)get_me_online(&data->index,
				&data->socket, argv[2], argv[3]);
	if (data->thread == 0)
	{
		mini_clean_exit(data);
		hpc_free(&data->socket, &data->index, data->thread);
		return (error_msg(ERR_ONLINE), 1);
	}
	return (0);
}

// dummy player
// t_player *lobby = lbb_get_ptr(NULL);
// ft_strlcpy(lobby[2].name, "dummy", 10);
// ft_strlcpy(lobby[2].name, "0.0.0.0", 10);
// lobby[2].pos[0] = 1091968148;
// lobby[2].pos[1] = 1094417599;
// lobby[2].pos[2] = 1065353216;
// lobby[2].tar[0] = 1095720131;
// lobby[2].tar[0] = 1120141309;
// lobby[2].tar[0] = 0;
// lobby[2].hp = PLAYER_HP;

int	main(int argc, char *argv[])
{
	t_multi_data	data;

	if (argc < 2 || argc > 4)
	{
		error_msg(ERR_ARGS);
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_multi_data));
	data.path = argv[1];
	if (argc == 2)
	{
		if (lbb_init() == NULL)
			return (1);
		ft_strlcpy(((t_player *)lbb_get_ptr(NULL))[HOST].name, "cub3D", 42);
		ft_strlcpy(((t_player *)lbb_get_ptr(NULL))[HOST].ip, "local", 15);
	}
	if (argc > 2)
	{
		if (online_setup(&data, argc, argv) == 1)
			return (1);
	}
	ft_printf("\n! ! ! CHECK LEAKS ON MULTI HOOST SWITCH ! ! !\n! ! ! INVALID READ ON OPEN MAP ! ! !\n");
	cub3d_bonus(&data);
	return (0);
}
