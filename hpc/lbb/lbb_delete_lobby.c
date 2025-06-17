/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_delete_lobby.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:33:52 by totommi           #+#    #+#             */
/*   Updated: 2025/06/17 20:11:45 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"

/* Clean way to free the whole player array */
void	lbb_delete_lobby(t_player *lobby)
{
	const void		*small = lbb_kill_player(NULL);
	unsigned int	i;

	if (lobby == NULL)
		return ;
	i = 0;
	while (i < MAXPLAYERS)
	{
		if (lobby[i].online >= small)
			free(lobby[i].online);
		i++;
	}
	free(lobby);
}
