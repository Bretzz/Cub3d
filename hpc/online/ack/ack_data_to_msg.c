/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ack_data_to_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:53:10 by totommi           #+#    #+#             */
/*   Updated: 2025/06/17 20:49:16 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
// #include <stdio.h>
// #include <string.h>

static size_t	special_length(char *ack_data)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (ack_data[i] != '\0')
	{
		if (ack_data[i] == ':'
			|| ack_data[i] == '\n')
			len++;
		len++;
		i++;
	}
	return (len);
}

static void	write_ack_data(char *ack_data, char *buff)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (ack_data[i] != '\0')
	{
		if (ack_data[i] == ':')
		{
			buff[i + j++] = ';';
			buff[i + j] = ';';
		}
		else if (ack_data[i] == '\n')
		{
			buff[i + j++] = '-';
			buff[i + j] = 'n';
		}
		else
			buff[i + j] = ack_data[i];
		i++;
	}
}

/* converts a string into an 'ack-msg' string with
special characters converted as in write_ack_data() */
/* buffsize >2xlen of ack_data
	+ MSG_NAME_LEN
	+ MSG_IP_LEN
	+ MSG_ACTION_LEN */
void	ack_data_to_msg(char *buff)
{
	size_t	size;

	if (buff == NULL)
		return ;
	*buff = '\0';
	if (*ack_data() == NULL)
		return ;
	size = special_length(*ack_data())
		+ MSG_NAME_LEN + MSG_IP_LEN + MSG_ACTION_LEN;
	ft_memset(buff, 0, size);
	ft_strlcat(buff, "-:-:", size);
	write_ack_data(*ack_data(), &buff[ft_strlen(buff)]);
	ft_strlcat(buff, "::", size);
	ft_strlcat(buff, "ack", size);
}
