/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:13:29 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/21 21:12:24 by scarlucc         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"

/* 0 = ok, 1 = error */
int	check_floor_ceiling(char *line, char	*start, t_mlx *mlx)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (check_single_floor(line, &mlx->map.floor))
			return (free(start), 1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (check_single_floor(line, &mlx->map.sky))
			return (free(start), 1);
	}
	return (0);
}

//0 = ok, 1 = error, 2 = found map
int	walls_ceiling_map(char *line, char *start, t_mlx *mlx)
{
	if ((ft_strncmp(line, "NO ", 3) == 0) || (ft_strncmp(line, "SO ", 3) == 0)
		|| (ft_strncmp(line, "WE ", 3) == 0)
		|| (ft_strncmp(line, "EA ", 3) == 0))
	{
		if (check_walls(line, start, mlx))
			return (1);
	}
	else if ((ft_strncmp(line, "F ", 2) == 0)
		|| (ft_strncmp(line, "C ", 2) == 0))
	{
		if (check_floor_ceiling(line, start, mlx))
			return (1);
	}
	else if (*line == '1')
		return (mlx->map.tmp_line = start, 2);
	else
		return (error_msg(ERR_CHAR_FILE), free(start), 1);
	return (0);
}

/* check texture walls and color ceiling and floor
0 = OK, 1 = error */
int	walls_ceiling(char *line, int fd, t_mlx *mlx)
{
	char	*start;
	int		result;

	while (line)
	{
		while (line && *line == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
		if (!line)
			break ;
		start = line;
		while (*line == ' ' || *line == '\t')
			line++;
		result = walls_ceiling_map(line, start, mlx);
		if (result == 1)
			return (1);
		else if (result == 2)
			return (0);
		free(start);
		line = get_next_line(fd);
	}
	return (0);
}

static char	**get_map(char *line, int fd, int i)
{
	char		**map;

	map = (char **)malloc(sizeof(char *));
	if (map == NULL)
		return (error_msg(MALLOC), close(fd), NULL);
	while (line != NULL)
	{
		map = ft_realloc(map, (i + 1) * sizeof(char *),
				(i + 2) * sizeof(char *));
		if (map == NULL)
			return (error_msg(MALLOC), close(fd), free(line), NULL);
		if (line[0] == '\n')
		{
			map[i] = trim_back_nl(line);
			return (map[++i] = NULL, error_msg(ERR_NEWLINE_MAP), close(fd),
				free_mtx((void **)map), NULL);
		}
		map[i] = trim_back_nl(line);
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	if (parsing_map(map, 0, 0) == 1)
		return (close(fd), free_mtx((void **)map), NULL);
	return (close(fd), map);
}

/* 0 = ok, 1 error */
int	parsing(const char *path, t_mlx *mlx)
{
	const int	fd = open(path, O_RDONLY);
	char		**map;
	char		*line;

	mlx->map.sky = UINT_MAX;
	mlx->map.floor = UINT_MAX;
	if (is_file_type(path, ".cub"))
		clean_exit(mlx, EXIT_FAILURE);
	if (fd < 0)
		return (error_msg(ERR_OPEN), clean_exit(mlx, EXIT_FAILURE), 1);
	line = get_next_line(fd);
	if (walls_ceiling(line, fd, mlx) != 0)
		return (close(fd), 1);
	if (mlx->map.sky == UINT_MAX || mlx->map.floor == UINT_MAX)
		return (error_msg(ERR_FC_MISS), close(fd), free(mlx->map.tmp_line), 1);
	if (mlx->map.no_wall == NULL || mlx->map.so_wall == NULL
		|| mlx->map.ea_wall == NULL || mlx->map.we_wall == NULL)
		return (error_msg(ERR_WALL_MISS), close(fd),
			free(mlx->map.tmp_line), 1);
	map = get_map(mlx->map.tmp_line, fd, 0);
	if (map == NULL)
		return (close(fd), 1);
	print_map(map);
	return (close(fd), mlx->map.mtx = map, 0);
}
