/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_stats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:09:17 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 18:13:57 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map_stats(const char **map, int win_x, int win_y, int *buff)
{
	unsigned int	i;
	int				max;
	size_t			len;

	if (map == NULL)
		return (0);
	max = 0;
	i = 0;
	while (map[i] != NULL)
	{
		len = ft_strlen(map[i]);
		if (len > (size_t)max)
			max = len;
		i++;
	}
	buff[0] = max;
	buff[1] = ft_mtxlen((void **)map);
	buff[2] = win_x / buff[0];
	if (buff[2] > win_y / buff[1])
		buff[2] = win_y / buff[1];
	if (DEBUG)
		ft_printf("got maX %d, maY %d, side %u\n", buff[0], buff[1], buff[2]);
	return (1);
}
