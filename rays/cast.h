/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:40:53 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 16:14:13 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAST_H
# define CAST_H

# include "cub3D.h"

typedef struct s_cast_vars
{
	float	angle;
	float	cos_angle;
	float	sin_angle;
	float	inv_cos;
	float	inv_sin;
	float	incr[2];
	int		axis[2];
	int		iter[2];
	int		curr;
}				t_cast_vars;

float	normalize_dir(float dir);

void	ray_init(t_ray *ray, float x, float y);
void	vars_init(t_ray *ray, t_cast_vars *cast, float dir);
int		out_of_bound(t_mlx *mlx, t_cast_vars *cast, float x, float y);
void	get_ray_data(t_mlx *mlx, t_cast_vars *cast, float x, float y);

#endif