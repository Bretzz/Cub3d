/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:35:17 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 17:20:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# define MY_PI 3.14159f
# define MY_PI_2 1.57079f

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

# define MAP_ALLOWED "01NSEW \n"

//array walls images
# define NO 0
# define SO 1
# define EA 2
# define WE 3

//errors
# define ERR_ARGS "	incorrect arguments number"
# define ERR_FORMAT "	incorrect file format"
# define ERR_OPEN "	failed to open path"
# define ERR_EMPTY_OR_FOLDER "	path points to empty file or folder"
# define ERR_WALL_REPEAT "	wall is repeated in scene description file"
# define ERR_FC_REPEAT "	floor or ceiling is repeated \
in scene description file"
# define ERR_FC_MISS "	floor or ceiling is missing in scene description file"
# define ERR_WALL_MISS "	wall is missing in scene description file"
# define ERR_FC_FORMAT "	color format invalid"
# define ERR_FC_BOUNDS "	color value out of bounds"
# define ERR_NEWLINE_MAP "	empty line in map"
# define ERR_OPEN_MAP "	open map"
# define ERR_NO_MAP "	missing map"
# define ERR_PATH_WALL "	wall path incorrect"
# define ERR_SPACE_END_PATH "	trim chars at end of wall path"
# define ERR_SPAWN "	map needs exactly ONE of the following chars: N S W E"
# define BAD_CHAR "	invalid character"
# define ERR_CHAR_FILE "	invalid character in scene description file"
# define MALLOC "	malloc failure"
# define ERR_ENVP " missing env variable(s)"
# define ERR_ONLINE "online setup failed"
# define ERR_IP_FORMAT "wrong IP format"
# define ERR_MALLOC "malloc failure"

# define RAY_COLOR 0xff0000

# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
//limits.h used to initialize floor and ceiling color values
# include <limits.h>

# ifdef __APPLE__
#  define __LINUX__ 0
#  define UP 126
#  define DOWN 125
#  define LEFT 123
#  define RIGHT 124
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define C_KEY 8
#  define M_KEY 46
#  define SPACE 49
#  define LSHIFT 257
#  define LALT 261
#  define PLUS 24
#  define MINUS 27
#  define ESC_KEY 53
# else
#  define __LINUX__ 1
#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363
#  define W_KEY 'w'
#  define A_KEY 'a'
#  define S_KEY 's'
#  define D_KEY 'd'
#  define C_KEY 'c'
#  define M_KEY 'm'
#  define SPACE ' '
#  define LSHIFT 65505
#  define LALT 65513
#  define PLUS 61
#  define MINUS 45
#  define ESC_KEY 65367
# endif 

# define MLX_WIN_X 1920
# define MLX_WIN_Y 1080

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

//online lib
# ifdef BONUS
#  include "hpc.h"
#  include "yft.h"
# endif

// basic sprite data
typedef struct s_sprite
{
	float			scale;
	int				height;
	int				width;
	void			*image;
	unsigned int	chroma;	// difference from the effective xpm file
}				t_sprite;

// data to help plotting the sprite
typedef struct s_plot
{
	float	scale;
	int		height;
	int		width;
	int		x_screen;
	int		y_screen;
	float	pos[3];
	float	dir;
	float	dist;
	int		seen;
}				t_plot;

// keys pressed
typedef struct s_keys
{
	int	up_dw[2];
	int	lx_rx[2];
	int	arrow[4];	// up, down, left, right
	int	jump_slide[2];
	int	shift;
	int	mouse[2];
	int	minimap;
}				t_keys;

// mlx img related data
typedef struct s_my_img
{
	void	*img_ptr;
	char	*data;
	int		bits_per_pixel;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_my_img;

// data of the map
typedef struct s_map
{
	char			**mtx;
	int				stats[3];	// max X, Y, side
	int				mini_side;
	char			*tmp_line;
	unsigned int	sky;
	unsigned int	floor;
	t_my_img		walls[4];
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

// player data
typedef struct s_local
{
	float		pos[3];				// pointer to the lobby's pos
	float		dir[3];				// 0/360 = west (x), front (y)
	int			fov[2];				// xvof, yfov
	int			speed[3];			// speed oriented on the map's axis
	int			o_speed[3];			// speed oriented on his axis (dir)
	float		tspeed[2];			// top speed (x,y), z
	float		jground;			// were the jump will end...
	int			friction;			// divider of the x_diff and y_diff
	t_sprite	*sprite;			// front, back, left, right
}				t_local;

# ifndef BONUS

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	t_my_img		img[2];
	t_map			map;
	t_keys			keys;
	char			on_window;
	int				frames;
	int				fps;
	t_ray			ray;
	t_local			player;

}				t_mlx;
# else

// online extension
typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	t_my_img		img[2];
	t_map			map;
	t_keys			keys;
	char			on_window;
	int				frames;
	int				fps;
	t_ray			ray;
	t_local			player;
	int				online;						// 1 online, 0 single
	t_plot			pos_data[MAXPLAYERS + 1];	// buffer for pos_get_dat()
	t_player		*lobby;						//online stuff here
	int				*index;
	int				*socket;
	t_player		fake_lobby[MAXPLAYERS];
	int				fake_index;
	unsigned long	thread;
}				t_mlx;

# endif

/* ============ GAME ============= */

int				move_player(t_mlx *mlx);
int				direction_oriented_movement(t_mlx *mlx);
int				move_mouse(t_mlx *mlx);

int				update_frame(void *arg);
int				get_fps(int frame);

int				handle_key_press(int keysym, void *arg);
int				handle_key_release(int keysym, void *arg);
int				handle_mouse(int keysym, int x, int y, t_mlx *mlx);
int				leave_notify_handler(t_mlx *mlx);
int				enter_notify_handler(t_mlx *mlx);

int				clean_exit(t_mlx *mlx, int exit_code);

/* ========== GRAPHICS ========== */

float			normalize_dir(float angle);
float			cast_ray(t_mlx *mlx, float x, float y, float dir);
int				cast_field(t_mlx *mlx,
					int (*func3d)(void *, int, float),
					int (*func2d)(void *, int, float, unsigned int));

void			my_pixel_put(void *my_struct, int x, int y,
					unsigned int color);
void			my_string_put(void *my_struct, int x, int y,
					const char *string);
void			my_number_put(void *my_struct, int x, int y, int nb);
void			image_pixel_put(void *img_ptr, int x, int y,
					unsigned int color);

unsigned int	get_pixel_color(void *img_ptr, int x, int y);

int				put_board(t_mlx *mlx);
int				put_square(t_my_img *img, size_t side, int *origin,
					unsigned int color);
int				put_line(t_my_img *img, int *p1, int *p2, unsigned int color);
int				put_whole_column(void *my_struct, int x, float len);

int				put2d_map(t_mlx *mlx, int side, unsigned int color);
int				put2d_ray(void *my_struct, int side, float null2,
					unsigned int color);
int				put2d_player(t_mlx *mlx, float *pos, int side,
					unsigned int color);

/* =========== PARSING =========== */

int				parsing(const char *path, t_mlx *mlx);
int				get_map_stats(const char **map, int win_x,
					int win_y, int *buff);

int				get_player_stats(char **map, float *pos, float *dir);
int				check_texture(t_mlx *mlx, char	*line, char *wall);
int				walls_ceiling(char *line, int fd, t_mlx *mlx);
int				parsing_map(char **map, int line, int count);

char			**map_padding(char **old_map);

int				just_one_player(char **map);
/* static int  	mapset_count(char **mtx, const char *set);
static int  	strset_count(const char *str, const char *set); */

/* =========== PARSING_UTILS =========== */

int				is_file_type(const char *file, const char *type);
int				ft_mapchr(char *str, const char *map);
int				check_single_floor(char	*line, unsigned int	*floor_ceiling);
int				check_single_wall(char	*line, char **wall);
int				check_path_walls(t_mlx *mlx);

/* =========== PARSING_MAP =========== */

int				check_walls(char *line, t_mlx *mlx);
int				parsing_map(char **map, int line, int count);
int				check_cross_help(int *i, char *allowed);
int				check_cross(char **map, int line, int count, char *allowed);

/* ============ UTILS ============= */

char			*trim_back_nl(char *str);
void			error_msg(char *msg);
void			error_msg2(char *msg, char print_char);
int				skip_spaces(char *line, int count);
int				check_rgb(char *rgb_value);

int				load_walls_texture(t_mlx *mlx);
int				is_white(char	*line);

/* ============ DEBUG ============= */

void			print_map(char **map);

#endif
