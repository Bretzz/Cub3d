/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:59:30 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/27 23:54:30 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define BONUS

# include "cub3D.h"
# include "hpc.h"
# include <pthread.h>

int	    put_sprite_on_map(t_mlx *mlx, float x, float y, t_sprite sprite);
int     put_player(t_mlx *mlx, float *pos, float *dir);

void    send_all(t_mlx *mlx, char *msg, size_t size, char flag);

void	free_fake_env(char **fake_env);

#endif