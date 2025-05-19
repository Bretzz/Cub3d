/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:35:17 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/19 19:17:31 by topiana-         ###   ########.fr       */
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
#  define MLX_WIN_X 500
# endif
# ifndef MLX_WIN_Y
#  define MLX_WIN_Y 500
# endif


# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct s_local
{
	float	pos[2];		// pointer to the lobby's pos
	int		fov[2];		// xvof, yfov
	int		dir[2];		// 0/360 = west (x), front (y)
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
}				t_mlx;

/* ============ GAME ============= */

int 	clean_exit(t_mlx *mlx);

/* ========== GRAPHICS ========== */

void	my_pixel_put(void *my_struct, int x, int y, unsigned int color);
int		put_square(t_mlx *mlx, size_t side, int x, int y, unsigned int color);
int		put_map(t_mlx *mlx, unsigned int color);

/* =========== PARSING =========== */

char	**parse_map(const char *path);
int		get_map_size(const char **map, int win_x, int win_y, int *buff);

/* ============ UTILS ============= */

void	free_mtx(void **mtx);
size_t	ft_mtxlen(const void **mtx);

/* ============ DEBUG ============= */

void	print_map(char **map);

#endif