/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_whole_column.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:38:02 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 02:52:50 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "puts.h"

int	put_whole_column(void *my_struct, int x, float len);

static void	vars_init(struct s_column_vars *vars,
	float len, t_my_img *my_wall, int wall_x)
{
	ft_memset(vars, 0, sizeof(struct s_column_vars));
	if (len < 0)
		vars->heigth = 0;
	else if (len == 0)
		vars->heigth = MLX_WIN_Y / 2;
	else
		vars->heigth = (MLX_WIN_X / 2) / len;
	vars->first_y = my_wall->data + (wall_x * my_wall->bpp);
	vars->wall_factor = (float)my_wall->heigth / (vars->heigth * 2);
}

static int	get_wall_x(t_ray *ray, t_my_img *walls)
{
	if (ray->face == 'V')
		return (0);
	if (ray->face < 2)
	{
		return (walls[(int)ray->face].width
			* (ray->hit[0] - (int)ray->hit[0]));
	}
	if (ray->face < 4)
	{
		return (walls[(int)ray->face].width
			* (ray->hit[1] - (int)ray->hit[1]));
	}
	return (0);
}

/* segfaults if len == 0 */
int	put_whole_column(void *my_struct, int x, float len)
{
	struct s_column_vars	vars;
	t_mlx *const			mlx = (t_mlx *)my_struct;
	const int				mid_line = MLX_WIN_Y / 2;
	const int				wall_x = get_wall_x(&mlx->ray, mlx->map.walls);
	t_my_img *const			my_wall = &mlx->map.walls[(int)mlx->ray.face];

	if (x < 0 || x >= MLX_WIN_X)
		return (1);
	vars_init(&vars, len, my_wall, wall_x);
	while (vars.y < MLX_WIN_Y)
	{
		if (vars.y < mid_line - vars.heigth)
			vars.put_color = mlx->map.sky;
		else if (vars.y < mid_line + vars.heigth)
			vars.put_color = *(unsigned int *)(vars.first_y + (int)((vars.y
							- (mid_line - vars.heigth)) * vars.wall_factor)
					*my_wall->line_length);
		else
			vars.put_color = mlx->map.floor;
		*(unsigned int *)(mlx->img->data + (vars.y * mlx->img->line_length)
				+ (x * mlx->img->bpp)) = vars.put_color;
		vars.y++;
	}
	return (0);
}
