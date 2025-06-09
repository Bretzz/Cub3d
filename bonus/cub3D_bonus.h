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
# define SPRITE_NUM 5

# include "cub3D.h"
# include "hpc.h"
# include <X11/Xlib.h>
# include <pthread.h>

/* data needed for the 'cub3D' thread
to talk with the 'online' thread. */
typedef struct s_multi_data
{
	char			*path;
	int				index;
	int				socket;
	unsigned long	thread;
	void			*mlx_ptr;
	void			*win_ptr;
}				t_multi_data;

/* BONUS PUTS */
int			put_sprite_on_map(t_mlx *mlx, float *pos, t_sprite sprite);
int			put_health_bar(t_mlx *mlx, t_plot plot, int hp);
int			put_player(t_mlx *mlx, t_player player, int action);
int			put_crosshair(t_mlx *mlx, unsigned int color);

/* BONUS LOADING */

t_sprite	*sprite_init(void *mlx_ptr, int i, unsigned int subst);
int			data_init(t_mlx *mlx, char *path, void *mlx_ptr, void *win_ptr);
int			online_data_init(t_mlx *mlx,
				int *index, int *socket, unsigned long thread);

/* BONUS INGAME */

void		send_all(t_mlx *mlx, char *msg, size_t size);
int			handle_player(t_mlx *mlx, t_player *lobby, int index);
int			move_and_slide(t_local *player, t_map map);

/* NONUS MATH */

float		dir_diff(float dir1, float dir2);

int			safe_hpc_read(int *ptr);

#endif