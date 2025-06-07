/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_health_bar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:41:34 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/07 16:34:26 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

# define BORDER 2

int put_health_bar(t_mlx *mlx, t_plot plot, int hp);

static void put_health_border(t_mlx *mlx, t_plot plot)
{
    const int   new_width = (PLAYER_HP * 5) * plot.scale;
    const int   new_heigth = (PLAYER_HP) * plot.scale;
    int         pixel[2];

    /* DOWN BORDER */
    pixel[0] = 0;
    while (pixel[0] < new_width)
    {
        pixel[1] = 0;
        while (pixel[1] < BORDER)
        {
            /* UP BORDER */
            my_pixel_put(mlx,
                pixel[0] + (plot.x_screen - (new_width / 2)),
                pixel[1] + (plot.y_screen - (new_heigth/*  / 2 */)),
                0x000000);  // 0x00cf00
            /* DOWN BORDER */
            my_pixel_put(mlx,
                pixel[0] + (plot.x_screen - (new_width / 2)),
                pixel[1] + (plot.y_screen /* + (new_heigth / 2) */),
                0x000000);  // 0x00cf00
            pixel[1]++;
        }
        pixel[0]++;
    }
    
    pixel[1] = 0;
    while (pixel[1] < new_heigth)
    {
        pixel[0] = 0;
        while (pixel[0] < BORDER)
        {
            /* LEFT BORDER */
            my_pixel_put(mlx,
                pixel[0] + (plot.x_screen - (new_width / 2)),
                pixel[1] + (plot.y_screen - (new_heigth/*  / 2 */)),
                0x000000);  // 0x00cf00
            /* RIGHT BORDER */
            my_pixel_put(mlx,
                pixel[0] + (plot.x_screen + (new_width / 2)),
                pixel[1] + (plot.y_screen - (new_heigth/*  / 2 */)),
                0x000000);  // 0x00cf00
            pixel[0]++;
        }
        pixel[1]++;
    }
}

static void put_health_fill(t_mlx *mlx, t_plot plot, int hp)
{
    const int   full = (PLAYER_HP * 5) * plot.scale;
    const int   hp_width = (hp * 5) * plot.scale;
    const int   new_heigth = (PLAYER_HP) * plot.scale;
    int         pixel[2];

    /* HP BAR */
    pixel[0] = 0;
    while (pixel[0] < full)
    {
        pixel[1] = 0;
        while (pixel[1] <  new_heigth)
        {
            if (pixel[0] < hp_width)
                my_pixel_put(mlx,
                    pixel[0] + (plot.x_screen - (full / 2)),
                    pixel[1] + (plot.y_screen - (new_heigth/*  / 2 */)),
                    0x00cf00);  // 0x00cf00
            else
                my_pixel_put(mlx,
                    pixel[0] + (plot.x_screen - (full / 2)),
                    pixel[1] + (plot.y_screen - (new_heigth/*  / 2 */)),
                    0xcf0000);  // 0x00cf00
            pixel[1]++;
        }
        pixel[0]++;
    }
}

/* puts an health bar on the coordinates (x, y). */
int put_health_bar(t_mlx *mlx, t_plot plot, int hp)
{
    if (hp < 0)
        return (1);

    // printf("got plot: x_screen %d, y_screen %d, heigth %d, scale %f\n",
    //     plot.x_screen,
    //     plot.y_screen,
    //     plot.heigth,
    //     plot.scale);
    plot.y_screen = plot.y_screen - ((plot.heigth / 2) * plot.scale);
    // put_sprite_health_bar(mlx,
    //     x_screen,
    //     mid_line + floor - ((sprite.heigth / 2) * sprite.scale),
    //     hp,	// hp here
    //     sprite.scale);

    // pixel[1] =
    put_health_fill(mlx, plot, hp);
    put_health_border(mlx, plot);
    return (0);
}
