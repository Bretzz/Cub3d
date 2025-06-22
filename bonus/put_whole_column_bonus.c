/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_whole_column_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:38:02 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 17:20:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	vars_init(struct s_column_vars_bonus *vars,
	float len, t_mlx *mlx, int wall_x)
{
	t_my_img *const	my_wall = &mlx->map.walls[(int)mlx->ray.face];

	ft_memset(vars, 0, sizeof(struct s_column_vars_bonus));
	if (len < 0)
		vars->height = 0;
	else if (len == 0)
		vars->height = MLX_WIN_Y;
	else
		vars->height = MLX_WIN_X / len;
	vars->first_y = my_wall->data + (wall_x * my_wall->bpp);
	vars->wall_factor = (float)my_wall->height / (vars->height);
	vars->z = vars->height / (mlx->player.pos[2] + 1);
	vars->cw = vars->z;
	vars->tw = vars->height - vars->z;
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

int	put_whole_column(void *my_struct, int x, float len)
{
	t_mlx *const				mlx = (t_mlx *)my_struct;
	const int					mid_line = cos(mlx->player.dir[1] * MY_PI / 180)
		* (2 * MLX_WIN_Y) + (MLX_WIN_Y / 2);
	const int					wall_x = get_wall_x(&mlx->ray, mlx->map.walls);
	t_my_img *const				my_wall = &mlx->map.walls[(int)mlx->ray.face];
	struct s_column_vars_bonus	vars;

	if (x < 0 || x >= MLX_WIN_X)
		return (1);
	vars_init(&vars, len, mlx, wall_x);
	while (vars.y < MLX_WIN_Y)
	{
		if (vars.y < mid_line - vars.cw)
			vars.put_color = mlx->map.sky;
		else if (vars.y < mid_line + vars.tw)
			vars.put_color = *(unsigned int *)(vars.first_y + (int)((vars.y
							- (mid_line - vars.cw)) * vars.wall_factor)
					*my_wall->line_length);
		else
			vars.put_color = mlx->map.floor;
		*(unsigned int *)(mlx->img->data + (vars.y * mlx->img->line_length)
				+ (x * mlx->img->bpp)) = vars.put_color;
		vars.y++;
	}
	return (0);
}
