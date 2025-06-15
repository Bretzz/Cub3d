/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:13:29 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/15 19:05:45 by scarlucc         ###   ########.fr       */
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

static char	**get_map(char		*line, int		fd)
{
	char		**map;
	int			i;

	i = 0;
	map = (char **)malloc(sizeof(char *));
	if (map == NULL)
		return (error_msg(MALLOC), close(fd), NULL);
	while (line != NULL)
	{
		map = ft_realloc(map, (i + 1) * sizeof(char *), (i + 2) * sizeof(char *));
		if (map == NULL)
			return (error_msg(MALLOC), close(fd), free(line), NULL);
		if (line[0] == '\n')
		{
			map[i] = trim_back_nl(line);
			map[++i] = NULL;
			return(error_msg(ERR_NEWLINE_MAP), close(fd), free_mtx((void **)map), NULL);
		}
		map[i] = trim_back_nl(line);
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	if (parsing_map(map, 0, 0) == 0)
		return(close(fd), free_mtx((void **)map), NULL);
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
//1 = OK, 0 = KO
int	parsing_map(char	**map, int	line, int	count)
{
	(void)count;
	char	**start;

	start = map;
	while (map[line] && !ft_mapchr(map[line], MAP_ALLOWED))
		line++;
	if (map[line] != NULL)
	{
		write(2, RED, ft_strlen(RED));
		ft_printfd(2, "Error\n	invalid char '%c' in map\n",
			ft_mapchr(map[line], MAP_ALLOWED));
		write(2, RESET, ft_strlen(RESET));
		return (0);
	} 
	
	return (1);
}

/*1 = OK, 0 = error */
int	check_walls(char	*line, char **wall)
{
	int	count;
	int	i;

	i = 0;
	//count = 2;
	/* while (line[count] == ' ')//sostituire con funzione apposita
		count++; */
	count = skip_spaces(line, 2);
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
	int		r;
	int		g;
	int		b;
	char	**rgb;

	if (*floor_ceiling != UINT_MAX)
		return (error_msg(ERR_FC_REPEAT), 0);
	else
	{
		rgb = ft_split(&line[1], ',');
		//printf("0 = %s\n 1 = %s\n 2 = %s\n\n ", rgb[0], rgb[1], rgb[2]);
		if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3]
			|| !check_rgb(rgb[0]) || !check_rgb(rgb[1]) || !check_rgb(rgb[2]))
			return (free_mtx((void **)rgb), error_msg(ERR_FC_FORMAT), 0);		
		r = ft_atoi(rgb[0]);
		g = ft_atoi(rgb[1]);
		b = ft_atoi(rgb[2]);
		//printf("r = %i\n g = %i\n b = %i\n ", r, g, b);
		if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
			return (free_mtx((void **)rgb), error_msg(ERR_FC_BOUNDS), 0);
		*floor_ceiling = (r << 16) | (g << 8) | b;
		/* printf("valore: %u\n", *floor_ceiling);
		printf("valore esadecimale: 0x%06X\n", *floor_ceiling); */
		free_mtx((void **)rgb);
		return (1);
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
			return (error_msg(ERR_EMPTY_OR_FOLDER), free(start), 0);
		while (line && *line == '\n') //forse mettere ft_isspace
		{
			free(line);
			line = get_next_line(fd);
		}
		if (!line)
			break; // fine file

		start = line;

		while (*line == ' ') //salta gli spazi iniziali, metti funzione apposita e forse modificala
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
			//return (parsing_map(line, mlx), free(start), 1);
			return (mlx->map.tmp_line = start, 1);
		else
			return(error_msg(ERR_CHAR_FILE), free(start), 0);//carattere non valido in file .cub
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
	const int	fd = open(path, O_RDONLY);
	char	**map;
	char	*line;

	if (!is_file_type(path, ".cub"))//wrong file format
		clean_exit(mlx);
	if (fd < 0)//file not found
		return (error_msg(ERR_OPEN), clean_exit(mlx), NULL);//serve close(fd)?
	//check informazioni su muri, pavimento e soffitto
	line = get_next_line(fd);

	if (walls_ceiling(line, fd, mlx) != 1)
		return (close(fd), NULL);
		
	//se manca pavimento o soffitto, errore
	if (mlx->map.sky == UINT_MAX || mlx->map.floor == UINT_MAX)
		return (error_msg(ERR_FC_MISS), close(fd), free(mlx->map.tmp_line), NULL);

	//se manca un muro, errore
	if (mlx->map.no_wall == NULL || mlx->map.so_wall == NULL
			|| mlx->map.ea_wall == NULL || mlx->map.we_wall == NULL)
		return (error_msg(ERR_WALL_MISS), close(fd), free(mlx->map.tmp_line), NULL);

	map = get_map(mlx->map.tmp_line, fd);
	if (map == NULL)
		return (close(fd), NULL);
	/* if (parsing_map(mlx) != 1)
		return (close(fd), NULL); */
	
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
