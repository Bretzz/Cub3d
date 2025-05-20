/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_stats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:52:23 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 16:08:10 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	pos[0] = j;
	pos[1] = i;
	if (map[i][j] == 'N')
		dir[0] = 90;
	if (map[i][j] == 'S')
		dir[0] = -90;
	if (map[i][j] == 'E')
		dir[0] = 180;
	if (map[i][j] == 'W')
		dir[0] = 0;
	return (0);
}
