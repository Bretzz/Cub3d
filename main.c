/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:07:13 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 13:41:42 by topiana-         ###   ########.fr       */
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
	mlx->win = mlx_new_window(mlx->mlx, MLX_WIN_X, MLX_WIN_Y, "cub3d");
	if (!mlx->win)
	{
		free(mlx->mlx);
		return (1);
	}
	return (0);
}

int	data_init(t_mlx *mlx)
{
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
	if (load_walls_texture(mlx))
		return (1);
	mlx->map.mtx = map_padding(mlx->map.mtx);
	if (mlx->map.mtx == NULL)
		return (1);
	get_map_stats((const char **)mlx->map.mtx,
		MLX_WIN_X, MLX_WIN_Y, mlx->map.stats);
	get_player_stats(mlx->map.mtx, mlx->player.pos, mlx->player.dir);
	mlx->map.mini_side = mlx->map.stats[2] / 4;
	mlx->frames = 1;
	return (0);
}

/* TO-DO: CHANGE SPEED TO INT (DONE)
SOMETIMES CRASHES NEAR THE BIG ORIZON (DONE-ish)
! ! ! COUNTER STRAFINNG ON THE RX EDGE ! ! ! */
int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	ft_memset(&mlx, 0, sizeof(t_mlx));
	if (argc != 2)
		return (error_msg(ERR_ARGS), 1);
	mlx.map.sky = UINT_MAX;
	mlx.map.floor = UINT_MAX;
	if (parsing(argv[1], &mlx))
		clean_exit(&mlx, EXIT_FAILURE);
	if (data_init(&mlx))
		clean_exit(&mlx, EXIT_FAILURE);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &handle_key_press, &mlx);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, &handle_key_release, &mlx);
	mlx_hook(mlx.win, DestroyNotify, StructureNotifyMask, &clean_exit, &mlx);
	mlx_loop_hook(mlx.mlx, &update_frame, &mlx);
	mlx_loop(mlx.mlx);
}
