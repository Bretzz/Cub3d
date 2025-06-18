/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:50:11 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 17:25:56 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**map_padding(char **old_map);

static int	get_longer_line(char **map)
{
	unsigned int	i;
	size_t			max;
	size_t			curr;

	max = ft_strlen(map[0]);
	i = 1;
	while (map[i] != NULL)
	{
		curr = ft_strlen(map[i]);
		if (curr > max)
			max = curr;
		i++;
	}
	return ((int)max);
}

static void	add_padding(char *new_line, int maxline, char padding)
{
	size_t	i;

	i = ft_strlen(new_line);
	while ((int)i < maxline)
	{
		new_line[i] = padding;
		i++;
	}
}

static char	*get_padded_line(char *old_line, int maxline, char padding)
{
	char	*new_line;

	new_line = (char *)ft_calloc(maxline + 1, sizeof(char));
	if (new_line == NULL)
		return (NULL);
	ft_strlcpy(new_line, old_line, maxline + 1);
	add_padding(new_line, maxline, padding);
	return (new_line);
}

char	**map_padding(char **old_map)
{
	const int			maxline = get_longer_line(old_map);
	const unsigned int	len = ft_mtxlen((void **)old_map);
	char				**new_map;
	unsigned int		i;

	new_map = (char **)ft_calloc(len + 1, sizeof(char *));
	if (new_map == NULL)
		return (free_mtx((void **)old_map), NULL);
	i = 0;
	while (i < len)
	{
		new_map[i] = get_padded_line(old_map[i], maxline, ' ');
		if (new_map[i] == NULL)
		{
			free_mtx((void **)old_map);
			free_mtx((void **)new_map);
			return (NULL);
		}
		i++;
	}
	free_mtx((void **)old_map);
	return (new_map);
}
