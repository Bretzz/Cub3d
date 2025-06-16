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

# ifndef BONUS
#  define BONUS
# endif

# define SPRITE_NUM 5
# define MINIMAP_OFFSET 30

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

/* BONUS ONLINE */

int			resign_exit(t_mlx *mlx);
void		send_all(t_mlx *mlx, char *msg, size_t size);

/* BONUS PUTS */

void		put_sprite(t_mlx *mlx, t_plot plot, t_sprite sprite);
int			put_sprite_on_map(t_mlx *mlx, float *pos, t_sprite sprite);
int			put_health_bar(t_mlx *mlx, t_plot plot, int hp);
int			put_crosshair(t_mlx *mlx, unsigned int color);

int			put2d_minimap(t_mlx *mlx, size_t side);
int			put2d_mini_ray(void *my_struct, int side,
				float null2, unsigned int color);
int			put2d_mini_lobby(t_mlx *mlx, size_t side);

/* BONUS LOADING */

t_sprite	*sprite_init(void *mlx_ptr, int i, unsigned int subst);
void		sprite_destroy(void *mlx_ptr, t_sprite *sprite);
int			data_init(t_mlx *mlx, void *mlx_ptr, void *win_ptr);
int			online_data_init(t_mlx *mlx,
				int *index, int *socket, unsigned long thread);

/* BONUS INGAME */

int			pos_get_data(t_mlx *mlx, float *pos, int index);
int			player_handle(t_mlx *mlx, t_player *fake_lobby);
int			player_put(t_mlx *mlx, t_player *fake_lobby);
int			move_and_slide(t_local *player, t_map map);

/* BONUS MATH */

float		dir_diff(float dir1, float dir2);

/* UTILS */

int			safe_hpc_read(int *ptr);
int			*operation_array(int *array, size_t size, int number, int operator);
float		*operation_arrayf(float *array, size_t size,
				float number, int operator);

#endif