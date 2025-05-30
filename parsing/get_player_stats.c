/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_stats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:52:23 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/30 14:33:29 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_dir(char player_char)
{
	if (player_char == 'N')
		return (90);
	if (player_char == 'S')
		return (-90);
	if (player_char == 'E')
		return (180);
	if (player_char == 'W')
		return (0);
	return (0);
}

/* LOBBY MUTEX */
int	get_player_stats(char **map, float *pos, float *dir)
{
	unsigned int	i;
	size_t			j;

	j = 0;
	i = 0;
	while (map[i] != NULL)
	{
		if (j == 0)
			j = ft_strichr(map[i], 'N');
		if (j == 0)
			j = ft_strichr(map[i], 'S');
		if (j == 0)
			j = ft_strichr(map[i], 'E');
		if (j == 0)
			j = ft_strichr(map[i], 'W');
		if (j != 0 && j--)
			break ;
		i++;
	}
	pos[0] = j + 0.5f;
	pos[1] = i + 0.5f;
	pos[2] = 1;
	dir[0] = get_dir(map[i][j]);
	dir[1] = 90;
	return (0);
}
