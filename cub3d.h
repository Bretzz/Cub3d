/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:35:17 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 12:17:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//colors
# define BOLD "\033[1m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

# ifndef MLX_WIN_X
#  define MLX_WIN_X 1000
# endif
# ifndef MLX_WIN_Y
#  define MLX_WIN_Y 500
# endif

# include <X11/X.h>
# include <X11/keysym.h>

# ifdef __APPLE__
#  define __APPLE__
#  define UP
#  define DOWN
#  define LEFT
#  define RIGHT
#  define W_KEY
#  define A_KEY
#  define S_KEY
#  define D_KEY
# else
#  define __LINUX__
#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363
#  define W_KEY 'w'
#  define A_KEY 'a'
#  define S_KEY 's'
#  define D_KEY 'd'
#  define SPACE ' '
#  define PLUS 61
#  define MINUS 45
#  define ESC_KEY 65367
# endif 

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_local
{
	float	pos[2];		// pointer to the lobby's pos
	int		fov[2];		// xvof, yfov
	float	dir[2];		// 0/360 = west (x), front (y)
	float	mspeed;
}				t_local;


typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

//mlx big struct
typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	int				win_x;
	int				win_y;
	t_img			img;
	t_local			player;
	char			**map;
	int				map_dim[3];					// max X, Y, side
	int				key_up_dw[2];
	int				key_lx_rx[2];
	int				mouse[2];
	char			on_window;
	int				frames;
	float			ray[2];
}				t_mlx;

/* ============ GAME ============= */

int 	update_frame(void *arg);

int		handle_key_press(int keysym, void *arg);
int		handle_key_release(int keysym, void *arg);
int		handle_mouse(int keysym, int x, int y, t_mlx *mlx);
int		leave_notify_handler(t_mlx *mlx);
int		enter_notify_handler(t_mlx *mlx);

int 	clean_exit(t_mlx *mlx);

/* ========== GRAPHICS ========== */

float 	normalize_dir(float angle);
float	cast_ray(t_mlx *mlx, float x, float y, float dir);
int		cast_field(t_mlx *mlx, int (*func)(void *, int, float, unsigned int));

int		put_board(t_mlx *mlx);
void	my_pixel_put(void *my_struct, int x, int y, unsigned int color);
int		put_square(t_mlx *mlx, size_t side, int x, int y, unsigned int color);
int		put_line(t_mlx *mlx, int *p1, int *p2, unsigned int color);
int		put_central_line(void *my_struct, int x, float len, unsigned int color);

int		put2d_map(t_mlx *mlx, int side, unsigned int color);
int		put2d_player(t_mlx *mlx, int side, unsigned int color);
int		put2d_ray(void *my_struct, int side, float null2, unsigned int color);
int		put2d_minimap(t_mlx *mlx, size_t side);

/* =========== PARSING =========== */

char	**parse_map(const char *path);
int		get_map_stats(const char **map, int win_x, int win_y, int *buff);

/* ============ UTILS ============= */

char	*trim_back_nl(char *str);

/* ============ DEBUG ============= */

void	print_map(char **map);

#endif