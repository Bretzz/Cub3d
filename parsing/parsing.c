/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:13:29 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 12:43:22 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**parsing(const char *path, t_mlx *mlx);

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
	if (line == NULL)
	{
		error_msg(ERR_EMPTY_OR_FOLDER);
		return (close(fd), free(map), NULL);
	}
	while (line != NULL)
	{
		map = ft_realloc(map, (i + 1) * sizeof(char *), (i + 2) * sizeof(char *));
		if (map == NULL)
		{
			ft_printfd(2, "Error: malloc failure\n");
			return (close(fd), free(line), NULL);
		}
		map[i] = trim_back_nl(line);
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
	if (ft_strncmp(&file[i], type, 5) != 0)
	{
		error_msg(ERR_FORMAT);
		return (0);
	}
	return (1);
}

void	check_texture(t_mlx *mlx, char	*line, char *wall)
{
	int	count;

	count = 2;
	while (line[count] == ' ')
		count++;
	if (ft_strcmp(wall, "NO") == 0)
		mlx->map.no_wall = ft_strdup(&line[count]);
	/* else if (ft_strcmp(wall, "SO") == 0)
		mlx->map.so_wall = ft_strdup(line[count]);
	else if (ft_strcmp(wall, "WE") == 0)
		mlx->map.we_wall = ft_strdup(line[count]);
	else if (ft_strcmp(wall, "EA") == 0)
		mlx->map.ea_wall = ft_strdup(line[count]); */
	printf("muro nord: %s\n", mlx->map.no_wall);
	/* printf("muro sud: %s\n", mlx->map.so_wall);
	printf("muro ovest: %s\n", mlx->map.we_wall);
	printf("muro est: %s\n", mlx->map.ea_wall); */
}

/* check texture walls and color ceiling and floor
1 = OK, 0 = error */
int	walls_ceiling(char *line, int fd, t_mlx *mlx)
{
	int	i;
	
	i = 0;
	while (line [i] == ' ') //salta gli spazi iniziali
		i++;
	
	while (line [i] == '\n') //forse mettere ft_isspace
	{
		free(line);
		line = get_next_line(fd);
		i = 0;
	}
	
	if (line == NULL)//empty file
		return (0);
	
	
	if (ft_strncmp(line, "NO ", 3) == 0)// presa texture pareti
		check_texture(mlx, line, "NO");
	/* else if (ft_strncmp(line, "SO ", 3) == 0)
		check_texture(mlx, line, "SO");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		check_texture(mlx, line, "WE");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		check_texture(mlx, line, "EA"); */
	return (1);
}

/* char * ok, 0 error */
char	**parsing(const char *path, t_mlx *mlx)
{
	int		fd;
	char	**map;
	int		i;
	char	*line;

	if (!is_file_type(path, ".cub"))//wrong file format
		//return (NULL);
		clean_exit(mlx);
	fd = open(path, O_RDONLY);
	//printf("fd = %d\n", fd);
	//close(fd);
	if (fd < 0)//file not found
	{
		error_msg(ERR_OPEN);//serve close(fd)?
		clean_exit(mlx);
		return (NULL);
	}
	//check informazioni su muri, pavimento e soffitto
	line = get_next_line(fd);
	


	if (walls_ceiling(line, fd, mlx) == 0)//empty file
	{
		error_msg(ERR_EMPTY_OR_FOLDER);
		close(fd);
		return (NULL);
	}


	/* while (line [0] == '\n') //forse mettere ft_isspace
	{
		free(line);
		line = get_next_line(fd);
	}
	
	if (line == NULL)//empty file
	{
		error_msg(ERR_EMPTY_OR_FOLDER);
		close(fd);
		return (NULL);
	}
	// presa texture pareti
	i = 0;
	while (line [i] == ' ') //salta gli spazi iniziali
		i++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		check_texture(mlx, line, "NO");
	/* else if (ft_strncmp(line, "SO ", 3) == 0)
		check_texture(mlx, line, "SO");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		check_texture(mlx, line, "WE");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		check_texture(mlx, line, "EA"); */

	
	free(line);
	map = get_map_from_path(path);
	if (map == NULL)
		return (NULL);
	//controllo caratteri mappa, commentato perche' interferisce con parsing altri parametri
	/* i = 0;
	while (map[i] && !ft_mapchr(map[i], "01NSEW \n"))
		i++;
	if (map[i] != NULL)
	{
		ft_printfd(2, "Error: invalid char '%c'\n", ft_mapchr(map[i], "01NSEW \n"));
		return (free_mtx((void **)map), clean_exit(mlx), NULL);
	} */
	print_map(map);
	close(fd);
	return (map);
}
