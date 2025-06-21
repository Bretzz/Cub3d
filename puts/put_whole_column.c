/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_whole_column.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:38:02 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/21 19:38:32 by scarlucc         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"
#include "puts.h"

int	put_whole_column(void *my_struct, int x, float len);

struct s_column_vars
{
	unsigned int	put_color;
	float			wall_factor;
	int				heigth;
	int				y;
};

int	get_wall_x(t_ray *ray, t_img *walls)
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
	t_mlx *const			mlx = (t_mlx *)my_struct;
	const int				mid_line = MLX_WIN_Y / 2;
	const int				wall_x = get_wall_x(&mlx->ray, mlx->map.walls);
	const t_img				*my_wall = &mlx->map.walls[(int)mlx->ray.face];
	struct s_column_vars	vars;

	if (x < 0 || x >= MLX_WIN_X)
		return (1);
	if (len < 0)
		vars.heigth = 0;
	else if (len == 0)
		vars.heigth = MLX_WIN_Y / 2;
	else
		vars.heigth = (MLX_WIN_X / 2) / len;
	vars.wall_factor = (float)my_wall->heigth / (vars.heigth * 2);
	vars.y = 0;
	while (vars.y < MLX_WIN_Y)
	{
		if (vars.y < mid_line - vars.heigth)
			vars.put_color = mlx->map.sky;
		else if (vars.y < mid_line + vars.heigth)
			vars.put_color = get_pixel_color(my_wall->img, wall_x,
				(vars.y - (mid_line - vars.heigth)) * vars.wall_factor);
		else
			vars.put_color = mlx->map.floor;
		*(unsigned int *)(mlx->img->addr + (vars.y * mlx->img->line_length)
				+ (x * mlx->img->bpp)) = vars.put_color;
		vars.y++;
	}
	return (0);
}
