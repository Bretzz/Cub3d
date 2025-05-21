/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:30:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 22:39:02 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key_press(int keysym, void *arg)
{
	t_mlx	*const mlx = (t_mlx *)arg;
	// char	buffer[92];

	if (keysym == XK_Escape || keysym == ESC_KEY)
	{
		// ft_printf("buffer is '%s'\n", buffer);
		clean_exit(mlx);
	}
	else if (keysym == XK_KP_Space || keysym == SPACE)
	{
		// ft_printf(BLUE"== = = == == =\n");
		// ft_printf("status: ");
		// if (*mlx->index == HOST)
		// 	ft_printf("HOST");
		// else
		// 	ft_printf("PLAYER");
		// ft_printf(", socket %d\n", *mlx->socket);
		// print_quick_lobby(mlx->lobby);
		// ft_printf(RESET);
		return (0);
	}
	else if ((keysym == XK_Up || keysym == UP)
		&& mlx->player.dir[1] - 5 >= 0)
		mlx->player.dir[1] -= 5;
	else if ((keysym == XK_Down || keysym == DOWN)
		&& mlx->player.dir[1] + 5 <= 180)
		mlx->player.dir[1] += 5;
	else if (keysym == XK_Left || keysym == LEFT)
		mlx->player.dir[0] -= 5;
	else if (keysym == XK_Right || keysym == RIGHT)
		mlx->player.dir[0] += 5;
	else if (keysym == XK_plus || keysym == PLUS)
		mlx->frames += 10;
	else if ((keysym == XK_minus || keysym == MINUS)
		&& mlx->frames >= 10)
		mlx->frames -= 10;
	else if (keysym == XK_w || keysym == W_KEY)
		mlx->key_up_dw[0] = 1;
	else if (keysym == XK_s || keysym == S_KEY)
		mlx->key_up_dw[1] = 1;
	else if (keysym == XK_a || keysym == A_KEY)
		mlx->key_lx_rx[0] = 1;
	else if (keysym == XK_d || keysym == D_KEY)
		mlx->key_lx_rx[1] = 1;
	else
		ft_printf("Key Pressed: %i\n", keysym);

	mlx->player.dir[0] = normalize_dir(mlx->player.dir[0]);
	mlx->player.dir[1] = normalize_dir(mlx->player.dir[1]);
	// ft_printf("dir[%d,%d]\n", mlx->player.dir[0], mlx->player.dir[1]);
	return (0);
}

int	handle_key_release(int keysym, void *arg)
{
	t_mlx	*const mlx = (t_mlx *)arg;

	if (keysym == XK_w || keysym == W_KEY)
		mlx->key_up_dw[0] = 0;
	else if (keysym == XK_s || keysym == S_KEY)
		mlx->key_up_dw[1] = 0;
	else if (keysym == XK_a || keysym == A_KEY)
		mlx->key_lx_rx[0] = 0;
	else if (keysym == XK_d || keysym == D_KEY)
		mlx->key_lx_rx[1] = 0;
	return (0);
}
