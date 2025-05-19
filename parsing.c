/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:13:29 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/19 19:20:30 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**parse_map(const char *path);

// cool stuff

int	ft_mapchr(char *str, const char *map);

/* checks if any char of map is in chr.
if a char that ISN'T in 'map' is found, returns 1,
otherwise returns 0 */
int	ft_mapchr(char *str, const char *map)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr(map, str[i]) == NULL)
			return (str[i]);
		i++;
	}
	return (0);
}

static char	**get_map_from_path(const char *path)
{
	const int	fd = open(path, O_RDONLY);
	char		**map;
	char		*line;
	int			i;

	i = 0;
	map = (char **)malloc(sizeof(char *));
	if (map == NULL)
	{
		ft_printfd(2, "Error: malloc failure\n");
		return (close(fd), NULL);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		map = ft_realloc(map, i + 1, i + 2);
		if (map == NULL)
		{
			ft_printfd(2, "Error: malloc failure\n");
			return (close(fd), free(line), NULL);
		}
		map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	return (close(fd), map);
}

/* check if the file type is the one passed,
1 ok, 0 ko. */
int	is_file_type(const char *file, const char *type)
{
	size_t	i;

	i = ft_strlen(file);
	while (i >= 0 && file[i] != '.')
		i--;
	if (ft_strcmp(&file[i], type) != 0)
		return (0);
	return (1);
}

/* char * ok, 0 error */
char	**parse_map(const char *path)
{
	const int	fd = open(path, O_RDONLY);
	char		**map;
	int			i;

	if (!is_file_type(path, ".cub"))
		return (NULL);
	close(fd);
	if (fd < 0)
	{
		ft_printfd(2, "Error: cannot open %s\n", path);
		return (NULL);
	}
	map = get_map_from_path(path);
	if (map == NULL)
		return (NULL);
	i = 0;
	while (map[i] && !ft_mapchr(map[i], "01NSEW"))
		i++;
	if (map[i] != NULL)
	{
		ft_printfd(2, "Error: invalid char '%c'\n", ft_mapchr(map[i], "01NSEW"));
		return (free_mtx((void **)map), NULL);
	}
	print_map(map);
	return (map);
}

int	get_map_size(const char **map, int win_x, int win_y, int *buff)
{
	unsigned int	i;
	int				max;
	size_t			len;

	if (map == NULL)
		return (0);
	max = -1;
	i = 0;
	while (map[i] != NULL)
	{
		len = ft_strlen(map[i]);
		if (len > (size_t)max)
			max = len;
		i++;
	}
	buff[0] = max;
	buff[1] = ft_mtxlen((const void **)map);
	buff[2] = win_x / buff[0];
	if (buff[2] > win_y / buff[1])
		buff[2] = win_y / buff[1];
	return (1);
}
