/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_press.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:30:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 17:37:36 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#ifdef BONUS

# include "cub3D_bonus.h"

static int	handle_movement_keys(int keysym, t_mlx *mlx);
static int	handle_arrow_keys(int keysym, t_mlx *mlx);
static int	handle_frame_keys(int keysym, t_mlx *mlx);

int	handle_key_press(int keysym, void *arg)
{
	t_mlx *const	mlx = (t_mlx *)arg;

	if (keysym == XK_Escape || keysym == ESC_KEY)
		resign_exit(mlx);
	else if (keysym == XK_0 || keysym == 29)
		ft_printf("pos[%d, %d, %d]\n",
			*(int *)&mlx->player.pos[0],
			*(int *)&mlx->player.pos[1],
			*(int *)&mlx->player.pos[2]);
	else if ((__LINUX__ && keysym == XK_1) || keysym == 18)
		print_lobby(mlx->fake_lobby);
	else if (handle_movement_keys(keysym, mlx))
		;
	else if (handle_arrow_keys(keysym, mlx))
		;
	else if (handle_frame_keys(keysym, mlx))
		;
	else if (DEBUG)
		ft_printf("Key Pressed: %i\n", keysym);
	return (0);
}

#else

static int	handle_movement_keys(int keysym, t_mlx *mlx);
static int	handle_arrow_keys(int keysym, t_mlx *mlx);
static int	handle_frame_keys(int keysym, t_mlx *mlx);

int	handle_key_press(int keysym, void *arg)
{
	t_mlx *const	mlx = (t_mlx *)arg;

	if (keysym == XK_Escape || keysym == ESC_KEY)
		clean_exit(mlx, EXIT_SUCCESS);
	else if (keysym == XK_0)
		ft_printf("pos[%d, %d, %d]\n",
			*(int *)&mlx->player.pos[0],
			*(int *)&mlx->player.pos[1],
			*(int *)&mlx->player.pos[2]);
	else if (handle_movement_keys(keysym, mlx))
		;
	else if (handle_arrow_keys(keysym, mlx))
		;
	else if (handle_frame_keys(keysym, mlx))
		;
	else if (DEBUG)
		ft_printf("Key Pressed: %i\n", keysym);
	return (0);
}

#endif

static int	handle_movement_keys(int keysym, t_mlx *mlx)
{
	if (keysym == XK_KP_Space || keysym == SPACE)
		mlx->keys.jump_slide[0] = 1;
	else if (keysym == 'c' || keysym == 8)
		mlx->keys.jump_slide[1] = 1;
	else if (keysym == XK_Shift_L || keysym == LSHIFT)
		mlx->keys.shift = 1;
	else if (keysym == XK_w || keysym == W_KEY)
		mlx->keys.up_dw[0] = 1;
	else if (keysym == XK_s || keysym == S_KEY)
		mlx->keys.up_dw[1] = 1;
	else if (keysym == XK_a || keysym == A_KEY)
		mlx->keys.lx_rx[0] = 1;
	else if (keysym == XK_d || keysym == D_KEY)
		mlx->keys.lx_rx[1] = 1;
	else
		return (0);
	return (1);
}

static int	handle_arrow_keys(int keysym, t_mlx *mlx)
{
	if ((keysym == XK_Up || keysym == UP)
		&& mlx->player.dir[1] - 5 >= 0)
		mlx->player.dir[1] -= 5;
	else if ((keysym == XK_Down || keysym == DOWN)
		&& mlx->player.dir[1] + 5 <= 180)
		mlx->player.dir[1] += 5;
	else if (keysym == XK_Left || keysym == LEFT)
		mlx->player.dir[0] -= 5;
	else if (keysym == XK_Right || keysym == RIGHT)
		mlx->player.dir[0] += 5;
	else
		return (0);
	return (1);
}

static int	handle_frame_keys(int keysym, t_mlx *mlx)
{
	if (keysym == XK_plus || keysym == PLUS)
	{
		mlx->frames += 10;
		mlx->player.tspeed[0] += 132;
		mlx->player.friction -= 3;
	}
	else if ((keysym == XK_minus || keysym == MINUS)
		&& mlx->frames > 10)
	{
		mlx->frames -= 10;
		mlx->player.tspeed[0] -= 132;
		mlx->player.friction += 3;
	}
	else if (keysym == XK_m || keysym == M_KEY)
		mlx->keys.minimap = (mlx->keys.minimap + 1) % 2;
	else
		return (0);
	return (1);
}
