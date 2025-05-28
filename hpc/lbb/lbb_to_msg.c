/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_to_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:40:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 01:27:04 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

/* converts the stat in player into an alloc'd msg-string.
RETURNS: the alloc'd msg-string pointer. */
void	*lbb_to_msg(t_player player)
{
	char	*msg;

	msg = (char *)malloc((MSG_LEN + 1) * sizeof(char));
	if (msg == NULL)
		return (NULL);
	ft_memset(msg, 0, (MSG_LEN + 1));
	ft_strlcpy(msg, player.name, ft_strlen(player.name) + 1);
	ft_strlcat(msg, ":", ft_strlen(msg) + 2);
	ft_strlcat(msg, player.ip, ft_strlen(msg) + ft_strlen(player.ip) + 1);
	ft_strlcat(msg, ":", ft_strlen(msg) + 2);
	rebuild_coord(player.pos, &msg[ft_strlen(msg)]);
	ft_strlcat(msg, ":", ft_strlen(msg) + 2);
	rebuild_coord(player.tar, &msg[ft_strlen(msg)]);
	return (msg);
}
