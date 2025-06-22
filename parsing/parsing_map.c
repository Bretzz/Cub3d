/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:56:30 by scarlucc          #+#    #+#             */
/*   Updated: 2025/06/22 13:28:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* 0 = ok, 1 = error */
int	check_walls(char *line, char	*start, t_mlx *mlx)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (check_single_wall(line, &mlx->map.no_wall))
			return (free(start), 1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (check_single_wall(line, &mlx->map.so_wall))
			return (free(start), 1);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (check_single_wall(line, &mlx->map.we_wall))
			return (free(start), 1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (check_single_wall(line, &mlx->map.ea_wall))
			return (free(start), 1);
	}
	return (0);
}

//0 = OK, 1 = error
int	parsing_map(char **map, int line, int c)
{
	while (map[line] && !ft_mapchr(map[line], MAP_ALLOWED))
		line++;
	if (map[line] != NULL)
		return (error_msg2(BAD_CHAR, ft_mapchr(map[line], MAP_ALLOWED)), 1);
	line = 0;
	while (map[line] != NULL)
	{
		if (map[line][c] == '\0')
		{
			line++;
			c = 0;
		}
		if (map[line] == NULL)
			break ;
		while (map[line][c] == '1' || map[line][c] == ' ')
			c++;
		if (map[line][c] != '\0' && check_cross(map, line, c, "01NSEW\0"))
			return (1);
		if (map[line][c] != '\0')
			c++;
	}
	if (just_one_player(map) != 0)
		return (error_msg(ERR_SPAWN), 1);
	return (0);
}

int	check_cross_help(int	*i, char	*allowed)
{
	if (allowed[*i] == '\0')
		return (1);
	*i = 0;
	return (0);
}

//0 = ok, 1 = error
int	check_cross(char **map, int line, int count, char *allowed)
{
	int	i;

	i = 0;
	if (line == 0 || map[line + 1] == NULL
		|| count == 0 || (count + 1) >= (int)ft_strlen(map[line]))
		return (error_msg(ERR_OPEN_MAP), 1);
	while (allowed[i] != '\0' && map[line -1][count] != allowed[i])
		i++;
	if (check_cross_help(&i, allowed))
		return (error_msg(ERR_OPEN_MAP), 1);
	while (allowed[i] != '\0' && map[line +1][count] != allowed[i])
		i++;
	if (check_cross_help(&i, allowed))
		return (error_msg(ERR_OPEN_MAP), 1);
	while (allowed[i] != '\0' && map[line][count -1] != allowed[i])
		i++;
	if (check_cross_help(&i, allowed))
		return (error_msg(ERR_OPEN_MAP), 1);
	while (allowed[i] != '\0' && map[line][count +1] != allowed[i])
		i++;
	if (allowed[i] == '\0')
		return (error_msg(ERR_OPEN_MAP), 1);
	return (0);
}
