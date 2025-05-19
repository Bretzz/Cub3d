/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:44:45 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 15:53:58 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "re_get_next_line.h"
#include "libft.h"

/* checks the list for a node with the corresponding 'fd'. */
static int	there_are_leftovers(int fd, t_list_fd *leftovers)
{
	if (leftovers == NULL)
		return (0);
	while (leftovers)
	{
		if (leftovers->fd == fd)
			return (1);
		leftovers = leftovers->next;
	}
	return (0);
}

static char	*what_was_left_behind(int fd, t_list_fd **leftovers)
{
	char			*line;

	while (*leftovers && (*leftovers)->fd != fd)
		*leftovers = (*leftovers)->next;
	if (*leftovers == NULL)
		return (NULL);
	line = ft_substr((*leftovers)->str, 0, -1);
	*leftovers = list_fd_del_fd(fd, *leftovers);
	return (line);
}

static char	*really_nice_line(int fd, char *line, t_list_fd **leftovers)
{
	unsigned int	i;
	char			*rnl;

	i = ft_strichr(line, '\n');
	rnl = ft_substr(line, 0, i);
	if (line[i] != '\0')
	{
		*leftovers = list_fd_add_back(*leftovers, fd, ft_strdup(&line[i]));
	}
	free(line);
	return (rnl);
}

char	*finally_read_from_fd(int fd, char *line, t_list_fd **leftovers)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	while (42)
	{
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0 && line == NULL)
			return (NULL);
		if (bytes_read < 0)
		{
			*leftovers = list_fd_del_fd(fd, *leftovers);
			free(line);
			return (NULL);
		}
		line = ft_strjoin_free(line, buffer);
		if (ft_strichr(line, '\n') != 0)
			return (really_nice_line(fd, line, leftovers));
		if (bytes_read == 0)
		{
			*leftovers = list_fd_del_fd(fd, *leftovers);
			return (line);
		}
	}
}

char	*get_next_line(int fd)
{
	static t_list_fd	*leftovers;
	char				*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = NULL;
	if (there_are_leftovers(fd, leftovers))
	{
		line = what_was_left_behind(fd, &leftovers);
	}
	if (ft_strichr(line, '\n') != 0)
	{
		line = really_nice_line(fd, line, &leftovers);
	}
	else
	{
		line = finally_read_from_fd(fd, line, &leftovers);
	}
	return (line);
}
