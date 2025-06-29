/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_health_bar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:41:34 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 17:20:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

#define BORDER 2

int	put_health_bar(t_mlx *mlx, t_plot plot, int hp);

static void	put_up_down_health_border(t_mlx *mlx, t_plot plot)
{
	const int	new_width = (PLAYER_HP * 5) * plot.scale;
	const int	new_height = (PLAYER_HP) * plot.scale;
	int			pixel[2];

	pixel[0] = 0;
	if (plot.x_screen < 0)
		pixel[0] = -plot.x_screen;
	while (pixel[0] < new_width
		&& pixel[0] + (plot.x_screen - (new_width / 2)) < MLX_WIN_X)
	{
		pixel[1] = 0;
		while (pixel[1] < BORDER)
		{
			my_pixel_put(&mlx->img,
				pixel[0] + (plot.x_screen - (new_width / 2)),
				pixel[1] + (plot.y_screen - (new_height)),
				0x000000);
			my_pixel_put(&mlx->img,
				pixel[0] + (plot.x_screen - (new_width / 2)),
				pixel[1] + (plot.y_screen),
				0x000000);
			pixel[1]++;
		}
		pixel[0]++;
	}
}

static void	put_left_right_health_border(t_mlx *mlx, t_plot plot)
{
	const int	new_width = (PLAYER_HP * 5) * plot.scale;
	const int	new_height = (PLAYER_HP) * plot.scale;
	int			pixel[2];

	pixel[1] = 0;
	if (plot.y_screen < 0)
		pixel[1] = -plot.y_screen;
	while (pixel[1] < new_height
		&& pixel[1] + (plot.y_screen - (new_height)) < MLX_WIN_Y)
	{
		pixel[0] = 0;
		while (pixel[0] < BORDER)
		{
			my_pixel_put(&mlx->img,
				pixel[0] + (plot.x_screen - (new_width / 2)),
				pixel[1] + (plot.y_screen - (new_height)),
				0x000000);
			my_pixel_put(&mlx->img,
				pixel[0] + (plot.x_screen + (new_width / 2)),
				pixel[1] + (plot.y_screen - (new_height)),
				0x000000);
			pixel[0]++;
		}
		pixel[1]++;
	}
}

/* HP BAR */
static void	put_health_fill(t_mlx *mlx, t_plot plot, int hp)
{
	const int	full = (PLAYER_HP * 5) * plot.scale;
	const int	hp_width = (hp * 5) * plot.scale;
	const int	new_height = (PLAYER_HP) * plot.scale;
	int			pixel[2];

	pixel[0] = 0;
	while (pixel[0] < full
		&& pixel[0] + (plot.x_screen - (full / 2)) < MLX_WIN_X)
	{
		pixel[1] = 0;
		while (pixel[1] < new_height
			&& pixel[1] + (plot.y_screen - (new_height)) < MLX_WIN_Y)
		{
			if (pixel[0] < hp_width)
				my_pixel_put(&mlx->img,
					pixel[0] + (plot.x_screen - (full / 2)),
					pixel[1] + (plot.y_screen - (new_height)), 0x00cf00);
			else
				my_pixel_put(&mlx->img,
					pixel[0] + (plot.x_screen - (full / 2)),
					pixel[1] + (plot.y_screen - (new_height)), 0xcf0000);
			pixel[1]++;
		}
		pixel[0]++;
	}
}

/* puts an health bar on the coordinates (x, y). */
int	put_health_bar(t_mlx *mlx, t_plot plot, int hp)
{
	if (hp < 0)
		return (1);
	plot.y_screen = plot.y_screen - ((plot.height / 2) * plot.scale);
	put_health_fill(mlx, plot, hp);
	put_up_down_health_border(mlx, plot);
	put_left_right_health_border(mlx, plot);
	return (0);
}
