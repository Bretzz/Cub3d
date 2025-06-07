/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:30:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/07 10:09:13 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_key_press(int keysym, void *arg)
{
	t_mlx *const	mlx = (t_mlx *)arg;

	if (keysym == XK_Escape || keysym == ESC_KEY)
	{
		clean_exit(mlx);
	}
	else if (keysym == XK_0)
	{
		ft_printf("pos[%d, %d, %d]\n", *(int *)&mlx->player.pos[0], *(int *)&mlx->player.pos[1], *(int *)&mlx->player.pos[2]);
	}
	else if (keysym == XK_KP_Space || keysym == SPACE)
		mlx->keys.jump_slide[0] = 1;
	else if (keysym == 'c' || keysym == 8)
		mlx->keys.jump_slide[1] = 1;
	else if (keysym == XK_Shift_L || keysym == LSHIFT)
		mlx->keys.shift = 1;
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
	{
		mlx->frames += 10;
		mlx->player.tspeed[0] += 132;
		mlx->player.friction -= 3;
		// mlx->player.jspeed += 35;
	}
	else if ((keysym == XK_minus || keysym == MINUS)
		&& mlx->frames > 10)
	{
		mlx->frames -= 10;
		mlx->player.tspeed[0] -= 132;
		mlx->player.friction += 3;	// not >= 0.5f
		// mlx->player.jspeed -= 35;
	}
	else if (keysym == XK_w || keysym == W_KEY)
		mlx->keys.up_dw[0] = 1;
	else if (keysym == XK_s || keysym == S_KEY)
		mlx->keys.up_dw[1] = 1;
	else if (keysym == XK_a || keysym == A_KEY)
		mlx->keys.lx_rx[0] = 1;
	else if (keysym == XK_d || keysym == D_KEY)
		mlx->keys.lx_rx[1] = 1;
	else
		ft_printf("Key Pressed: %i\n", keysym);
	// ft_printf("dir[%f, %f]\n", mlx->player.dir[0], mlx->player.dir[1]);
	return (0);
}

int	handle_key_release(int keysym, void *arg)
{
	t_mlx *const	mlx = (t_mlx *)arg;

	if (keysym == XK_KP_Space || keysym == SPACE)
		mlx->keys.jump_slide[0] = 0;
	else if (keysym == XK_c ||  keysym == C_KEY || keysym == 8)
		mlx->keys.jump_slide[1] = 0;
	else if (keysym == XK_Shift_L || keysym == LSHIFT)
		mlx->keys.shift = 0;
	else if (keysym == XK_w || keysym == W_KEY)
		mlx->keys.up_dw[0] = 0;
	else if (keysym == XK_s || keysym == S_KEY)
		mlx->keys.up_dw[1] = 0;
	else if (keysym == XK_a || keysym == A_KEY)
		mlx->keys.lx_rx[0] = 0;
	else if (keysym == XK_d || keysym == D_KEY)
		mlx->keys.lx_rx[1] = 0;
	return (0);
}
