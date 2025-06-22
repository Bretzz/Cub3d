/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_strip_comments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 04:25:00 by totommi           #+#    #+#             */
/*   Updated: 2025/06/21 17:25:19 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int		yft_strip_comments(char *file);

// static int	is_white(char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (!ft_isspace(str[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

/* passed a pointer to the beginning of the comment */
static int	clear_weird_comment(char *line)
{
	size_t	i;

	i = 0;
	while ((line[i] != '*' || line[i + 1] != '/'))
	{
		if (line[i] == '\0')
		{
			*line = '\0';
			return (1);
		}
		i++;
	}
	ft_memmove(line, &line[i + 2], ft_strlen(&line[i + 2]) + 1);
	return (0);
}

/* passed a pointer to the beginning of the comment */
static int	clear_standard_comment(char *line)
{
	size_t	i;

	i = 0;
	while ((line[i] != '\n'))
	{
		if (line[i] == '\0')
		{
			*line = '\0';
			return (1);
		}
		i++;
	}
	ft_memmove(line, &line[i + 2], ft_strlen(&line[i + 2]) + 1);
	return (0);
}

/* both '/ *' and '//' comments handled */
static void	strip_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '/' && line[i + 1] == '/')
		{
			if (clear_standard_comment(&line[i]))
				return ;
		}
		if (line[i] == '/' && line[i + 1] == '*')
		{
			if (clear_weird_comment(&line[i]))
				return ;
		}
		i++;
	}
}

int	yft_strip_comments(char *file)
{
	if (file == NULL)
		return (1);
	strip_line(file);
	return (0);
}

// int main(void)
// {
// 	char	line[] = "line to strip /* properly  */, gotchu? // fr man";

// 	strip_line(line);
// 	ft_printf("'%s'\n", line);
// 	return (0);
// }