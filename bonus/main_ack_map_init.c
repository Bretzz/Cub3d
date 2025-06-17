/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ack_map_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:50:44 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/17 20:55:58 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	ack_map_init(t_multi_data *data);

static char	*read_whole_file(char *path)
{
	char		*line;
	char		*whole_file;
	const int	fd = open(path, O_RDONLY);

	if (fd < 0)
		return (NULL);
	whole_file = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		whole_file = ft_strjoin_free(whole_file, line);
		free(line);
		if (whole_file == NULL)
			return (close(fd), NULL);
		line = get_next_line(fd);
	}
	return (close(fd), whole_file);
}

/* writes a file with the string passed */
static int	write_whole_file(char *whole_file)
{
	const int	fd = open("online.cub", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (fd < 0)
	{
		ft_printfd(2, RED"Error\ncreating online.cub%s\n", RESET);
		return (1);
	}
	if (write(fd, whole_file, ft_strlen(whole_file)) < 0)
		return (close(fd), 1);
	return (close(fd), 0);
}

static void	wait_for_server_ack(void)
{
	int	i;

	i = 0;
	while (*ack_data() == NULL && i++ < 10)
		usleep(1000);
}

/* singleplayer: do nothing
	server: loads the 'ack_data()' buffer with
		the content of the map.
	client: waits for the 'ack_data()' bufferr to be filled
		in the online thread, then writes the content
		of the 'ack_data()' buffer into a file (online.cub)
		that will be treated as the passed map.  */
int	ack_map_init(t_multi_data *data)
{
	if (ACK_DATA == 0 || data->socket == 0)
		return (1);
	if (data->index == HOST)
	{
		if (*ack_data() != NULL)
			free(*ack_data());
		*ack_data() = read_whole_file(data->path);
		if (*ack_data() == NULL)
			return (0);
	}
	else if (data->index == PLAYER)
	{
		wait_for_server_ack();
		if (*ack_data() == NULL)
			return (0);
		if (write_whole_file(*ack_data()) != 0)
			return (0);
		ft_memset(data->path, 0, ft_strlen(data->path));
		ft_strlcpy(data->path, "online.cub", 11);
	}
	return (1);
}
