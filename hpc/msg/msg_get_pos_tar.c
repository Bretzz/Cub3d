/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_get_pos_tar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:34:46 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 01:29:22 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg.h"

char	*msg_get_pos_tar(const char *msg, char *pos_tar);

/* expected a buffer of size >71
Takes a msg-string and an char pointer as parameters.
Assign the vaues writen in msg to pos_tar using strlcpy(3).
RETURNS: the pos_tar pointer, NULL if pos_tar is NULL.
NOTE: copies the end part of the msg-string 'X_Y_Z:X_Y_Z' into 'pos_tar'. */
char	*msg_get_pos_tar(const char *msg, char *buffer)
{
	char	coord[15];
	int		pos[3];
	int		tar[3];

	if (buffer == NULL)
		return (NULL);
	ft_memset(buffer, 0, ((MSG_DATA_LEN * 2) + 2) * sizeof(char));
	if (msg == NULL)
		return (buffer);
	if (!has_pos(msg))
		return (buffer);
	msg_get_pos(msg, pos);
	ft_strlcpy(buffer, rebuild_coord(pos, coord), 16);
	if (!has_tar(msg))
		return (buffer);
	ft_strlcat(buffer, ":", ft_strlen(buffer) + 2);
	msg_get_tar(msg, tar);
	ft_strlcat(buffer, rebuild_coord(tar, coord),
		ft_strlen(buffer) + ft_strlen(coord) + 1);
	return (buffer);
}
