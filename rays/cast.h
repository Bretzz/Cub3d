/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:40:53 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/08 17:45:18 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAST_H
# define CAST_H

# include "cub3D.h"

typedef struct s_cast_vars
{
	float	*ray;
	float	angle;
	float	incr[2];
	int		axis[2];
	int		iter[2];
}				t_cast_vars;

float	normalize_dir(float dir);

void	ray_init(t_ray *ray, float x, float y);
void	vars_init(t_ray *ray, t_cast_vars *cast, float dir);
int		out_of_bound(t_mlx *mlx, float *ray);
int		get_next_border(int axis, float start, int i);

#endif