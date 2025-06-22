/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:50:33 by scarlucc          #+#    #+#             */
/*   Updated: 2025/06/22 13:28:10 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* check if the file type is the one passed,
0 ok, 1 ko. */
int	is_file_type(const char *file, const char *type)
{
	int	i;

	i = ft_strlen(file);
	while (i >= 0 && file[i] != '.')
	{
		i--;
		if (i <= 0)
			return (error_msg(ERR_FORMAT), 1);
	}
	if (ft_strncmp(&file[i], type, (ft_strlen(type) + 1)) != 0)
	{
		error_msg(ERR_FORMAT);
		return (1);
	}
	return (0);
}

/* checks if any char of map is in str.
if a char that ISN'T in 'map' is found, returns that char,
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

/*0 = OK, 1 = error */
int	check_single_wall(char	*line, char **wall)
{
	int	count;
	int	i;

	i = 0;
	count = skip_spaces(line, 2);
	if (*wall)
		return (error_msg(ERR_WALL_REPEAT), 1);
	else
	{
		*wall = ft_strdup(&line[count]);
		while ((*wall)[i] && (*wall)[i] != '\n')
			i++;
		(*wall)[i] = '\0';
		if (is_file_type(*wall, ".xpm"))
			return (1);
	}
	return (0);
}

/*0 = OK, 1 = error */
int	check_single_floor(char	*line, unsigned int	*floor_ceiling)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	if (*floor_ceiling != UINT_MAX)
		return (error_msg(ERR_FC_REPEAT), 1);
	else
	{
		rgb = ft_split(&line[1], ',');
		if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3]
			|| !check_rgb(rgb[0]) || !check_rgb(rgb[1]) || !check_rgb(rgb[2]))
			return (free_mtx((void **)rgb), error_msg(ERR_FC_FORMAT), 1);
		r = ft_atoi(rgb[0]);
		g = ft_atoi(rgb[1]);
		b = ft_atoi(rgb[2]);
		if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
			return (free_mtx((void **)rgb), error_msg(ERR_FC_BOUNDS), 1);
		*floor_ceiling = (r << 16) | (g << 8) | b;
		free_mtx((void **)rgb);
		return (0);
	}
	return (0);
}
