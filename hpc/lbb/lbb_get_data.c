/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:29:48 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 14:05:23 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"
# include "libft.h"
# include "msg.h"

char	*lbb_get_full_stats(t_player player, void *buffer);

/* converst all the data in the player struct to a msg-string
the string is then copied into buffer and returned the buffer pointer.
If buffer is NULL, returns NULL, otherwise player stats are copied.
EXPECTED: buffer of size >MSG_LEN */
char	*lbb_get_full_stats(t_player player, void *buffer)
{
	char	*msg;

	if (buffer == NULL)
		return (NULL);
	ft_memset(buffer, 0, MSG_LEN);
	msg = lbb_to_msg(player);
	if (msg == NULL)
		return (buffer);
	ft_strlcpy(buffer, msg, MSG_LEN);
	free(msg);
	return (buffer);
}

/* Expected a buffer of size >(MSG_LEN * MAXPLAYERS).
lbb_get_full_stats call on the whole lobby, separated by '\n' */
char	*lbb_get_lobby_stats(t_player *lobby, void *buffer)
{
	const size_t	player_count = lbb_player_count();
	char			*buffer_c;
	unsigned int	count;
	unsigned int	i;

	if (buffer == NULL)
		return (buffer);
	ft_memset(buffer, 0, MSG_LEN * MAXPLAYERS);
	if (lobby == NULL)
		return (buffer);
	buffer_c = (char *)buffer;
	count = 0;
	i = 0;
	while (i < MAXPLAYERS && count < player_count)
	{
		if (lbb_is_alive(lobby[i]))
		{
			lbb_get_full_stats(lobby[i], &buffer_c[(count * MSG_LEN) + count]);
			count++;
			if (count < player_count)
				ft_strlcat(buffer_c, "\n", MSG_LEN * MAXPLAYERS);
		}
		i++;
	}
	return (buffer);
}
