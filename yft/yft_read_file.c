/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:57:24 by totommi           #+#    #+#             */
/*   Updated: 2025/06/21 17:25:31 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"
#include <fcntl.h>

int	yft_read_file(const char *path, char **file);

/* reads the whole file into a matrix of strings */
int	yft_read_file(const char *path, char **file)
{
	char	*line;
	int		fd;

	if (file == NULL)
		return (1);
	(*file) = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (3);
	line = get_next_line(fd);
	while (line != NULL)
	{
		(*file) = ft_strjoin_free((*file), line);
		if ((*file) == NULL)
			return (close(fd), 1);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}

// int main(void)
// {
// 	char	*file;
// 	char	*monoline;

// 	yft_read_file("my_cool_font.yft", &file);

// 	ft_printf("= = == = READ  == = = =\n%s", file);
// 	// print_file(file);
// 	yft_strip_comments(file);
// 	// print_file(file);
// 	yft_monoline_file(file, &monoline);
// 	ft_printf("monoline '%s'\n", monoline);
// 	return (0);
// }
