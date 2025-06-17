/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ack_data_from_msg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:29:47 by totommi           #+#    #+#             */
/*   Updated: 2025/06/17 20:00:50 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"

static size_t	get_data_len(const char *msg)
{
	const int	data = str_skip(msg, 2, ':');
	size_t		len;

	len = 0;
	while (msg[data + len] && msg[data + len] != ':')
		len++;
	return (len);
}

/* name:ip:DATA::ack */
static int	crop_data_from_msg(const char *msg, char **buff)
{
	const size_t	len = get_data_len(msg);
	const int		data = str_skip(msg, 2, ':');
	size_t			i;

	if (buff == NULL)
		return (1);
	*buff = (char *)malloc((len + 1) * sizeof(char));
	if (*buff == NULL)
		return (1);
	ft_memset(*buff, 0, (len + 1) * sizeof(char));
	i = 0;
	while (i < len)
	{
		(*buff)[i] = msg[data + i];
		i++;
	}
	return (0);
}

/* special characters:
	1. ';;' -> ':'
	2. '-n' -> '\n' */
static void	special_chars_converter(char *buff)
{
	size_t	i;

	i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == ';' && buff[i + 1] == ';')
		{
			ft_memmove(&buff[i], &buff[i + 1], ft_strlen(&buff[i]));
			buff[i] = ':';
		}
		if (buff[i] == '-' && buff[i + 1] == 'n')
		{
			ft_memmove(&buff[i], &buff[i + 1], ft_strlen(&buff[i]));
			buff[i] = '\n';
		}
		i++;
	}
}

/* writes the content of the 'ack-msg' into
a dynamically allocated memory stored into ack_data() */
void	ack_data_from_msg(const char *msg)
{
	if (crop_data_from_msg(msg, (char **)ack_data()) != 0)
		return ;
	special_chars_converter(*ack_data());
}
