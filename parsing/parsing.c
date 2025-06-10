/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:13:29 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/10 19:08:13 by scarlucc         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
		error_msg(ERR_EMPTY_OR_FOLDER);//forse mettere errore diverso
		return (close(fd), free(map), NULL);
	}

	// va fino alla linea della mappa (molto abbozzato)
	while (line != NULL && !ft_strchr(line, '1'))
	{
		free(line);
		line = get_next_line(fd);
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

void	parsing_map(char	*line, t_mlx *mlx)
{
	(void)line;
	(void)mlx;
	printf("trovata mappa\n");
}

/*1 = OK, 0 = error */
int	check_walls(char	*line, char **wall)
{
	int	count;
	int	i;

	count = 2;
	i = 0;
	while (line[count] == ' ')
		count++;
	if (*wall)
		return (error_msg(ERR_WALL_REPEAT), 0);
	else
	{
		*wall = ft_strdup(&line[count]);
		while ((*wall)[i] && (*wall)[i] != '\n')
			i++;
		(*wall)[i] = '\0';
	}
	return (1);	
}

/*1 = OK, 0 = error */
int	check_fc(char	*line, unsigned int	*floor_ceiling)
{
	int		count;
	int		i;
	/* int		red;
	int		green;
	int		blue; */
	char	*rgb = NULL;
	

	count = 1;
	i = 0;
	if (*floor_ceiling != 0)
		return (error_msg(ERR_FC_REPEAT), 0);
	else
	{
		
		count = skip_spaces(line, count);
		while (ft_isdigit(line[count]))
		{
			count++;
			i++;
		}
		if (i > 3 || i == 0)
			return (error_msg(ERR_FC_FORMAT), 0);
		else
		{
			ft_strlcpy(rgb, &line[count - i], (i + 1));
			printf("numero estratto: %s\n", rgb);
		}
			
		
		
	}
	return (1);
}

/* check texture walls and color ceiling and floor
1 = OK, 0 = error */
int	walls_ceiling(char *line, int fd, t_mlx *mlx)
{
	char	*start;
	int		err;

	err = 1;
	while (line)
	{		
		start = line;
		if (line == NULL || *line == '\0')//empty file or missing map
			return (free(start), 0);
		
		while (line && *line == '\n') //forse mettere ft_isspace
		{
			free(line);
			line = get_next_line(fd);
		}
		if (!line)
			break; // fine file

		start = line;

		while (*line == ' ') //salta gli spazi iniziali
			line++;
		if (ft_strncmp(line, "NO ", 3) == 0)
			err = check_walls(line, &mlx->map.no_wall);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			err = check_walls(line, &mlx->map.so_wall);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			err = check_walls(line, &mlx->map.we_wall);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			err = check_walls(line, &mlx->map.ea_wall);
		else if (ft_strncmp(line, "F ", 2) == 0)//pavimento
			err = check_fc(line, &mlx->map.floor);
		else if (ft_strncmp(line, "C ", 2) == 0)//soffitto
			err = check_fc(line, &mlx->map.sky);
		else if (*line == '1')
			return (parsing_map(line, mlx), free(start), 1);
		else
			return(free(start), 0);//mappa aperta o carattere non valido in file .cub
		//per proseguire dopo aver letto una riga corretta, dopo mettere in funzione separata
		free(start);
		if (err == 0)
			clean_exit(mlx);
		line = get_next_line(fd);
	}
	return (1);
}

/* char * ok, 0 error */
char	**parsing(const char *path, t_mlx *mlx)
{
	int		fd;
	char	**map;
	//int		i;
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
