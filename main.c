/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:07:13 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/21 19:08:15 by scarlucc         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"

/*set up the pc-side of the t_data (mlx) struct
RETURNS: 0 all good, 1 error*/
static int	juice_the_pc(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	// mlx->win_x = MLX_WIN_X;
	// mlx->win_y = MLX_WIN_Y;
	mlx->win = mlx_new_window(mlx->mlx, MLX_WIN_X, MLX_WIN_Y, "cub3d");
	if (!mlx->win)
	{
		free(mlx->mlx);
		return (1);
	}
	return (0);
}

int load_single_wall(void *mlx_ptr, t_img *wall, char *path)
{
	wall->img = mlx_xpm_file_to_image(mlx_ptr, path, &wall->width, &wall->heigth);
	if (wall->img == NULL)
		return (1);
	wall->addr =  mlx_get_data_addr(wall->img, &wall->bits_per_pixel, &wall->line_length, &wall->endian);
	wall->bpp = wall->bits_per_pixel >> 3;
	return (0);
}

int	load_walls_textures(t_mlx *mlx)
{
	if (load_single_wall(mlx->mlx, &mlx->map.walls[NO], mlx->map.no_wall))
		return (1);
	if (load_single_wall(mlx->mlx, &mlx->map.walls[SO], mlx->map.so_wall))
		return (1);
	if (load_single_wall(mlx->mlx, &mlx->map.walls[EA], mlx->map.ea_wall))
		return (1);
	if (load_single_wall(mlx->mlx, &mlx->map.walls[WE], mlx->map.we_wall))
		return (1);
	// mlx->map.walls[NO].img = mlx_xpm_file_to_image(mlx->mlx, mlx->map.no_wall, &mlx->map.walls[NO].width, &mlx->map.walls[NO].heigth);
	// if (mlx->map.walls[NO].img == NULL)
	// 	return (1);
	// mlx->map.walls[NO].addr =  mlx_get_data_addr(mlx->map.walls[NO].img, &mlx->map.walls[NO].bits_per_pixel, &mlx->map.walls[NO].line_length, &mlx->map.walls[NO].endian);
	// mlx->map.walls[NO].bpp = mlx->map.walls[NO].bits_per_pixel >> 3;
	return (0);
}

int	data_init(t_mlx *mlx)
{
	/* (void)argc;(void)argv; */
	
	mlx->player.fov[0] = 60;
	mlx->player.fov[1] = 60;
	mlx->player.speed[0] = 0;
	mlx->player.speed[1] = 0;
	mlx->player.speed[2] = 0;
	mlx->player.tspeed[0] = 200.0f;
	mlx->player.tspeed[1] = 300;
	mlx->player.jground = 1;
	mlx->player.friction = 1;
	if (juice_the_pc(mlx))
		return (1);
	if (load_walls_textures(mlx))
		return (1);
	mlx->map.mtx = map_padding(mlx->map.mtx);
	if (mlx->map.mtx == NULL)
		return (1);
	get_map_stats((const char **)mlx->map.mtx, MLX_WIN_X, MLX_WIN_Y, mlx->map.stats);
	get_player_stats(mlx->map.mtx, mlx->player.pos, mlx->player.dir);
	mlx->map.mini_side = mlx->map.stats[2] / 4;
	mlx->frames = 1;	// do not insert a multiple of 10
	return (0);	
}

/* TO-DO: CHANGE SPEED TO INT (DONE)
SOMETIMES CRASHES NEAR THE BIG ORIZON (DONE-ish)
! ! ! COUNTER STRAFINNG ON THE RX EDGE ! ! ! */
int main(int argc, char *argv[])
{
	t_mlx	mlx;

	ft_memset(&mlx, 0, sizeof(t_mlx));
	if (argc != 2)
		return (error_msg(ERR_ARGS), 1);//this check needs to precede open path in parsing, in case argc == 1
	if (parsing(argv[1], &mlx/* , mlx */))
		clean_exit(&mlx, EXIT_FAILURE);
	if (data_init(&mlx))
		clean_exit(&mlx, EXIT_FAILURE);

	// key hooks
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &handle_key_press, &mlx);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, &handle_key_release, &mlx);

	// mouse hook
	// mlx_mouse_hook(mlx.win, &handle_mouse, &mlx);

	// on window hooks
	// mlx_hook(mlx.win, EnterNotify, (1L << 4), &enter_notify_handler, &mlx);
	// mlx_hook(mlx.win, LeaveNotify, (1L << 5), &leave_notify_handler, &mlx);

	// red cross
	mlx_hook(mlx.win, DestroyNotify, StructureNotifyMask, &clean_exit, &mlx);

	// frame updater
	mlx_loop_hook(mlx.mlx, &update_frame, &mlx);

	mlx_loop(mlx.mlx);
}
