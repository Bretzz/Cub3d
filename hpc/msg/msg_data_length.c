/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_data_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:24:58 by totommi           #+#    #+#             */
/*   Updated: 2025/05/28 14:03:13 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg.h"

size_t	msg_ip_length(const char *msg);
size_t	msg_name_length(const char *msg);

/* EXPECTED: a msg string, null terminated,
RETUSNS: the length of the name, 0 if 'msg' is NULL. */
size_t	msg_name_length(const char *msg)
{
	size_t	i;

	if (msg == NULL)
		return (0);
	i = 0;
	while (msg[i] != '\0' && msg[i] != ':' && i < MSG_NAME_LEN)
		i++;
	return (i);
}

/* EXPECTED: a msg string, null terminated,
RETUSNS: the length of the ip, 0 if 'msg' is NULL. */
size_t	msg_ip_length(const char *msg)
{
	size_t	name;
	size_t	i;

	if (msg == NULL)
		return (0);
	name = msg_name_length(msg);
	if (msg[name++] == '\0')
		return (0);
	i = 0;
	while (msg[name + i] != '\0' && msg[name + i] != ':' && i < MSG_IP_LEN)
		i++;
	return (i);
}
