/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:18:50 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/19 20:56:55 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*his_sidekick(int fd, char *line, t_list_fd *trubbish,
				t_list_fd **leftovers);
static char	*the_magician(int fd, char *line, char *buff,
				t_list_fd **leftovers);
static char	*munchlax(int fd, t_list_fd *curr_lefties);

/*check if the_magiciasn actually did something:
if he didn't (we reached EOL or an error occured), returns NULL
if the trick (line) of the_magician doesn't contain a new_line,
	return the whole trick
if it does create a substr of the elements after the '\n',
clear/create curr_lefties content and assigne the substr pointer to it,
then returns a substr of the chars of line up to the '\n' (included)
than frees the line
trubbish is a temp_leftovers*/
static char	*his_sidekick(int fd, char *line, t_list_fd *trubbish,
				t_list_fd **leftovers)
{
	char	*new_line;

	if (!ft_strichr(line, '\n') || !line[ft_strichr(line, '\n')])
	{
		ft_lstclear_fd(fd, leftovers, &free);
		return (line);
	}
	while (trubbish && trubbish->next && trubbish->fd != fd)
		trubbish = trubbish->next;
	if (!trubbish || (!trubbish->next && trubbish->fd != fd))
		trubbish = ft_lstnew_add_back_ptr(fd, trubbish, NULL);
	else if (trubbish->fd == fd)
		free(trubbish->content);
	if (!trubbish)
	{
		free (line);
		return (NULL);
	}
	if (!(*leftovers))
		*leftovers = trubbish;
	trubbish->content = ft_substr(line, ft_strichr(line, '\n'),
			ft_strlen(line));
	new_line = ft_substr(line, 0, ft_strichr(line, '\n'));
	free(line);
	return (new_line);
}

/*reads up to '\n' and returns the string read
if BUFFER_SIZE > 1 the char found after '\n' aren't returned but
stored in leftovers*/
static char	*the_magician(int fd, char *line, char *buff, t_list_fd **leftovers)
{
	int	i;

	while (42)
	{
		i = 0;
		while (i <= BUFFER_SIZE)
			buff[i++] = '\0';
		i = read(fd, buff, BUFFER_SIZE);
		if (i <= 0)
			break ;
		if (line == (char *)42 || line == (char *)2)
			line = NULL;
		line = ft_strjoin_free(line, buff);
		if (!line)
			return (NULL);
		if (ft_strichr(buff, '\n'))
			break ;
	}
	if (i <= 0 && !(!i && (line != (char *)42 && line != (char *)2) && *line))
	{
		if (line != (char *)42 && line != (char *)2)
			free(line);
		return (NULL);
	}
	return (his_sidekick(fd, line, *leftovers, leftovers));
}

/*looks for a node with the current fd, if found
checks if there's a newline in the leftovers of the previous call
if so returns the line up to that point and updates leftovers,
if there isn't returns ((char *)42) and leaves leftovers as it is.
(all of this while moving the original leftover pointer)
If no node with curr fd is found returns ((char *)42)*/
static char	*munchlax(int fd, t_list_fd *curr_lefties)
{
	char		*new_lefties;
	char		*line;

	if (!curr_lefties)
		return ((char *)2);
	while (curr_lefties->next && curr_lefties->fd != fd)
		curr_lefties = curr_lefties->next;
	if (curr_lefties->fd != fd)
		return ((char *)42);
	if (!ft_strichr(curr_lefties->content, '\n'))
	{
		line = ft_substr(curr_lefties->content, 0,
				ft_strlen(curr_lefties->content));
		return (line);
	}
	line = ft_substr(curr_lefties->content, 0,
			ft_strichr(curr_lefties->content, '\n'));
	if (!line)
		return (NULL);
	new_lefties = ft_substr(curr_lefties->content,
			ft_strichr(curr_lefties->content, '\n'),
			ft_strlen(curr_lefties->content));
	free(curr_lefties->content);
	curr_lefties->content = new_lefties;
	return (line);
}

char	*get_next_line(int fd)
{
	static void			*leftovers;
	char				*line;
	char				buff[BUFFER_SIZE];

	line = munchlax(fd, (t_list_fd *)leftovers);
	if (line == NULL)
		return (NULL);
	else if ((line != (char *)42 && line != (char *)2)
		&& (ft_strichr(line, '\n')))
		return (line);
	line = the_magician(fd, line, buff, (t_list_fd **)&leftovers);
	if (!line)
		ft_lstclear_fd(fd, (t_list_fd **)&leftovers, &free);
	return (line);
}
