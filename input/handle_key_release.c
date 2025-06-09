/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_release.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:15:13 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 20:16:06 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_key_release(int keysym, void *arg);

int	handle_key_release(int keysym, void *arg)
{
	t_mlx *const	mlx = (t_mlx *)arg;

	if (keysym == XK_KP_Space || keysym == SPACE)
		mlx->keys.jump_slide[0] = 0;
	else if (keysym == XK_c || keysym == C_KEY || keysym == 8)
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
