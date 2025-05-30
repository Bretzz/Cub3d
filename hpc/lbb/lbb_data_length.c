/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_data_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:50:33 by totommi           #+#    #+#             */
/*   Updated: 2025/05/30 19:10:46 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"
#include "libft.h"
#include "msg.h"

size_t	lbb_name_length(const char *name);
size_t	lbb_ip_length(const char *ip);

/* EXPECTED: a char[MSG_NAME_LEN], null terminated,
if the space was enough.
RETUSNS: the length of the name, 0 if 'name' is NULL. */
size_t	lbb_name_length(const char *name)
{
	size_t	i;

	if (name == NULL)
		return (0);
	i = 0;
	while (name[i] != '\0' && i < MSG_NAME_LEN)
		i++;
	return (i);
}

/* EXPECTED: a char[MSG_IP_LEN], null terminated,
if the space was enough.
RETUSNS: the length of the ip, 0 if 'ip' is NULL. */
size_t	lbb_ip_length(const char *ip)
{
	size_t	i;

	if (ip == NULL)
		return (0);
	i = 0;
	while (ip[i] != '\0' && i < MSG_IP_LEN)
		i++;
	return (i);
}
