/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:12:37 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/20 22:57:02 by totommi          ###   ########.fr       */
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
	ft_memset(buffer, 0, (86 + 6) * sizeof(char));
	lbb_get_full_stats(player, buffer);
	ft_strlcat(buffer, ":", (86 + 6) * sizeof(char));
	ft_strlcat(buffer, action, (86 + 6) * sizeof(char));
	return (buffer);
}

/* EXPECTED buffer of size >(86 + 6 + 1) * MAXPLAYERS
86 = player stats, 6 = action, 1 = newline, 1 = null term */
char	*buffer_lobby_action(t_player *lobby, const char *action, void *buffer)
{
	const size_t	player_count = lbb_player_count();
	unsigned int	i;
	unsigned int	count;
	unsigned char	*buffer_c;

	if (buffer == NULL)
		return (NULL);
	ft_memset(buffer, 0, ((86 + 6 + 1) * MAXPLAYERS) + 1 * sizeof(char));
	buffer_c = (unsigned char *)buffer;
	count = 0;
	i = 0;
	while (i < MAXPLAYERS && count < player_count)
	{
		if (lbb_is_alive(lobby[i]))
		{
			buffer_player_action(lobby[i], action, &buffer_c[ft_strlen(buffer)]);
			count++;
			if (count < player_count)
				ft_strlcat(buffer, "\n", ((86 + 6 + 1) * MAXPLAYERS) + 1);
		}
		i++;
	}
	return (buffer);
}
