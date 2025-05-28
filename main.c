/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:07:13 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 12:01:08 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*set up the pc-side of the t_data (mlx) struct
RETURNS: 0 all good, 1 error*/
static int	juice_the_pc(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win_x = MLX_WIN_X;
	mlx->win_y = MLX_WIN_Y;
	mlx->win = mlx_new_window(mlx->mlx, MLX_WIN_X, MLX_WIN_Y, "cub3d");
	if (!mlx->win)
	{
		free(mlx->mlx);
		return (1);
	}
	return (0);
}

int	data_init(t_mlx *mlx, int argc, char *argv[])
{
	/* (void)argc;(void)argv; */
	if (argc != 2)
	{
		error_msg(ERR_ARGS);
		exit(1);
	}
	ft_memset(mlx, 0, sizeof(t_mlx));
	if (juice_the_pc(mlx))
		return (1);
	mlx->player.fov[0] = 60;
	mlx->player.fov[1] = 60;
	mlx->player.dir[1] = 90;
	mlx->player.speed[0] = 0;
	mlx->player.speed[1] = 0;
	mlx->player.speed[2] = 0;
	mlx->player.tspeed[0] = 300.0f;
	mlx->player.tspeed[1] = 300;
	mlx->player.jground = 1;
	mlx->player.friction = 1;
	mlx->map.mtx = parsing(argv[1], mlx);
	if (mlx->map.mtx == NULL)
		//return (1);
		clean_exit(mlx);
	get_map_stats((const char **)mlx->map.mtx, mlx->win_x, mlx->win_y, mlx->map.stats);
	get_player_stats(mlx->map.mtx, mlx->player.pos, mlx->player.dir);
	mlx->map.sky = 0xadd8e6;
	mlx->map.floor = 0xcaf0d5;
	mlx->frames = 21;	// do not insert a multiple of 10
	return (0);	
}

int main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (data_init(&mlx, argc, argv))
		clean_exit(&mlx);

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

	// frame updater
	mlx_loop_hook(mlx.mlx, &update_frame, &mlx);

	ft_printf("TO-DO: CHANGE SPEED TO INT (DONE)\nSOMETIMES CRASHES NEAR THE BIG ORIZON (DONE-ish)\n! ! ! COUNTER STRAFINNG ON THE RX EDGE ! ! !\n");

	mlx_loop(mlx.mlx);
}
