/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:12:37 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/07 17:08:08 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "online.h"

/* Fills the buffer with 'name:ip:pos:tar:action'
EXPECTED: buffer of size >92 */
char	*buffer_player_action(t_player player, const char *action, void *buffer)
{
	if (buffer == NULL)
		return (NULL);
	ft_memset(buffer, 0, (MSG_LEN + 6) * sizeof(char));
	lbb_get_full_stats(player, buffer);
	ft_strlcat(buffer, ":", (MSG_LEN + 6) * sizeof(char));
	ft_strlcat(buffer, action, (MSG_LEN + 6) * sizeof(char));
	return (buffer);
}

/* EXPECTED buffer of size >(MSG_LEN + 6 + 1) * MAXPLAYERS
MSG_LEN = player stats, 6 = action, 1 = newline, 1 = null term */
/* LOBBY MUTEX */
char	*buffer_lobby_action(t_player *lobby, const char *action, void *buffer)
{
	size_t			player_count;
	unsigned int	i;
	unsigned int	count;
	unsigned char	*buffer_c;

	if (buffer == NULL)
		return (NULL);
	ft_memset(buffer, 0, (((MSG_LEN + 6 + 1) * MAXPLAYERS) + 1) * sizeof(char));
	buffer_c = (unsigned char *)buffer;
	lbb_mutex(1);
	player_count = lbb_player_count();
	count = 0;
	i = 0;
	while (i < MAXPLAYERS && count < player_count)
	{
		if (lbb_is_alive(lobby[i]))
		{
			buffer_player_action(lobby[i],
				action, &buffer_c[ft_strlen(buffer)]);
			if (++count < player_count)
				ft_strlcat(buffer, "\n", ((MSG_LEN + 6 + 1) * MAXPLAYERS) + 1);
		}
		i++;
	}
	return (lbb_mutex(2), buffer);
}
