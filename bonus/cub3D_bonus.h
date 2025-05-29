/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:59:30 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/27 23:54:30 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define BONUS

# include "cub3D.h"
# include "hpc.h"
# include <X11/Xlib.h>
# include <pthread.h>

int	    put_sprite_on_map(t_mlx *mlx, float *pos, t_sprite sprite, int chroma);
int     put_health_bar(t_mlx *mlx, t_plot plot, int hp);
int     put_player(t_mlx *mlx, t_player player, int action, int chroma);
int		put_crosshair(t_mlx *mlx, unsigned int color);

void	send_all(t_mlx *mlx, char *msg, size_t size, char flag);

int		handle_player(t_mlx *mlx, t_player *lobby, int index);

float	dir_diff(float dir1, float dir2);

#endif