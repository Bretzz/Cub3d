/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_name_tag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:45:48 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 13:12:14 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	put_name_tag(t_mlx *mlx, t_plot plot, const char *name)
{
	const int	new_width = (PLAYER_HP * 5) * plot.scale;

	plot.y_screen = plot.y_screen - (((float)plot.heigth / 1.6f) * plot.scale);
	plot.x_screen = plot.x_screen - (new_width / 2.3f);
	my_string_put(&mlx->img, plot.x_screen, plot.y_screen, name);
	return (0);
}
