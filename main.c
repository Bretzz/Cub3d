/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:07:13 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/19 19:21:44 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	(void)argc; (void)argv;
	ft_memset(mlx, 0, sizeof(t_mlx));
	if (juice_the_pc(mlx))
		return (1);
	mlx->player.pos[0] = 2;								// arbitrary position X
	mlx->player.pos[1] = 2;								// arbitrary position Y
	mlx->player.fov[0] = 90;
	mlx->player.fov[1] = 0;
	mlx->player.dir[0] = 0;
	mlx->player.dir[1] = 0;
	mlx->map = parse_map("map.cub");
	if (mlx->map == NULL)
		return (1);
	get_map_size((const char **)mlx->map, mlx->win_x, mlx->win_y, mlx->map_dim);
	return (0);	
}


static int	put_board(t_mlx *mlx)
{	
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->win_x, mlx->win_y);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img
			.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.img || !mlx->img.addr)
		return (0);

	put_map(mlx, 0xff0000);
	// put_grid(mlx);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	//ft_printf("ccc\n");
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	//ft_printf("the board is put\n");
	return (1);
}

int main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (data_init(&mlx, argc, argv))
		return (1);

	put_board(&mlx);

	mlx_loop(mlx.mlx);
}
