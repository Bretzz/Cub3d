/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:35:17 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 12:38:11 by topiana-         ###   ########.fr       */
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

//errors
# define ERR_ARGS "	incorrect arguments number"
# define ERR_FORMAT "	incorrect file format"
# define ERR_OPEN "	failed to open path"
# define ERR_EMPTY_OR_FOLDER "	path points to empty file or folder"
# define ERR_CHAR "	invalid character in map"

# ifndef MLX_WIN_X
#  define MLX_WIN_X 1000
# endif
# ifndef MLX_WIN_Y
#  define MLX_WIN_Y 1000
# endif

# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>

# ifdef __APPLE__
#  define UP 126
#  define DOWN 125
#  define LEFT 123
#  define RIGHT 124
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define SPACE 49
#  define LSHIFT 257
#  define LALT 261
#  define PLUS 24
#  define MINUS 27
#  define ESC_KEY 53
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
#  define LSHIFT 65505
#  define LALT 65513
#  define PLUS 61
#  define MINUS 45
#  define ESC_KEY 65367
# endif 

# ifndef MLX_WIN_X
#  define MLX_WIN_X 1000
# endif
# ifndef MLX_WIN_Y
#  define MLX_WIN_Y 1000
# endif

// graphic libs
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>


// basic libs
# include "libft.h"
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

// basic sprite data
typedef struct s_sprite
{
	float	scale;
	int		heigth;
	int		width;
	void	*image;
}				t_sprite;

// player data
typedef struct s_local
{
	float		pos[3];		// pointer to the lobby's pos
	int			fov[2];		// xvof, yfov
	float		dir[2];		// 0/360 = west (x), front (y)
	int			speed[3];	// speed oriented on the map's axis
	int			o_speed[3];	// speed oriented on his axis (dir)
	float		tspeed[2];	// top speed (x,y), z
	float		jground;	// were the jump will end...
	int			friction;	// divider of the x_diff and y_diff
	t_sprite	sprite[4];	// front, back, left, right
}				t_local;

// keys pressed
typedef struct s_keys
{
	int	up_dw[2];
	int	lx_rx[2];
	int	jump_slide[2];
	int	shift;
	int	mouse[2];
}				t_keys;

// data of the map
typedef struct s_map
{
	char			**mtx;
	int				stats[3];	// max X, Y, side
	unsigned int	sky;
	unsigned int	floor;
	char			*no_wall;
	char			*so_wall;
	char			*we_wall;
	char			*ea_wall;
}				t_map;

// ray data
typedef struct s_ray
{
	float	len;		// length of the ray
	float	hit[2];		// coord of the point hit
	char	face;		// 'N', 'S', 'E', 'W', 'V' (V = 'Void')
}				t_ray;

// mlx img related data
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

// mlx big struct
# ifndef BONUS

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	int				win_x;
	int				win_y;
	t_img			img;
	t_map			map;
	t_keys			keys;
	char			on_window;
	int				frames;
	int				fps;
	t_ray			ray;
	t_local			player;

}				t_mlx;
# else

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	int				win_x;
	int				win_y;
	t_img			img;
	t_map			map;
	t_keys			keys;
	char			on_window;
	int				frames;
	int				fps;
	t_ray			ray;
	t_local			player;
	// t_player		*lobby;
	int				*index;
	int				*socket;
	void			*thread;
}				t_mlx;

# endif

// //mlx big struct
// typedef struct s_mlx
// {
// 	void			*mlx;
// 	void			*win;
// 	int				win_x;
// 	int				win_y;
// 	t_img			img;
// 	t_map			map;
// 	t_keys			keys;
// 	char			on_window;
// 	int				frames;
// 	int				fps;
// 	t_ray			ray;
// 	t_local			player;
// # ifdef BONUS
// 	// t_player		*lobby;
// 	int				*index;
// 	int				*socket;
// 	void			*thread;
// # endif
// }				t_mlx;

/* ============ GAME ============= */

int				move_player(t_mlx *mlx);
int				direction_oriented_movement(t_mlx *mlx);
int				move_mouse(t_mlx *mlx);

int 			update_frame(void *arg);

int				handle_key_press(int keysym, void *arg);
int				handle_key_release(int keysym, void *arg);
int				handle_mouse(int keysym, int x, int y, t_mlx *mlx);
int				leave_notify_handler(t_mlx *mlx);
int				enter_notify_handler(t_mlx *mlx);

int 			clean_exit(t_mlx *mlx);

/* ========== GRAPHICS ========== */

float 			normalize_dir(float angle);
float			cast_ray(t_mlx *mlx, float x, float y, float dir);
int				cast_field(t_mlx *mlx, int (*func)(void *, int, float, unsigned int));

void			my_pixel_put(void *my_struct, int x, int y, unsigned int color);
unsigned int	get_pixel_color(void *sprite, int x, int y);

int				put_board(t_mlx *mlx);
int				put_square(t_mlx *mlx, size_t side, int *origin, unsigned int color);
int				put_line(t_mlx *mlx, int *p1, int *p2, unsigned int color);
int				put_whole_column(void *my_struct, int x, float len, unsigned int color);

int				put2d_map(t_mlx *mlx, int side, unsigned int color);
int				put2d_player(t_mlx *mlx, int side, unsigned int color);
int				put2d_ray(void *my_struct, int side, float null2, unsigned int color);
int				put2d_minimap(t_mlx *mlx, size_t side);

/* =========== PARSING =========== */

char			**parsing(const char *path, t_mlx *mlx);
int				get_map_stats(const char **map, int win_x, int win_y, int *buff);

int				get_player_stats(char **map, float *pos, float *dir);
void			check_texture(t_mlx *mlx, char	*line, char *wall);

/* ============ UTILS ============= */

char			*trim_back_nl(char *str);
void			error_msg(char *msg);


/* ============ DEBUG ============= */

void			print_map(char **map);

#endif