/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:07:12 by totommi           #+#    #+#             */
/*   Updated: 2025/05/28 20:34:53 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"
# include "libft.h"
# include "msg.h"

void	*lbb_init(void);
void	*lbb_get_ptr(t_player *new_lobby);

/* Confron a stack allocated memory address and
an heap allocated one, then passes the lowest to
lbb_kill_player so that it can be stored.
NOTE: based on the system this method could fail. */
static void	lbb_kill_threshold_init(void)
{
	const char	small = 0x7f;
	void		*tiny;

	lbb_kill_player(&small);
	tiny = malloc(1);
	if (tiny == NULL)
		return ;
	*(char *)tiny = 0x7f;
	if (tiny < (void *)&small)
		lbb_kill_player(tiny);
	free(tiny);
}

/* initialize the lbb_get_ptr's ptr to a
malloc'd t_player array of size MAXPLAYERS.
RETURN it's pointer. 
ALSO you can pass a pointer to somewher and that
will be considered the smallest pointer value under
wich the pointer will be considered corrupted. */
void	*lbb_init(void)
{
	t_player	*lobby;

	lbb_kill_threshold_init();
	lobby = lbb_get_ptr(NULL);
	free(lobby);
	lobby = (t_player *)malloc(MAXPLAYERS * sizeof(t_player));
	if (lobby == NULL)
		return (NULL);
	ft_memset(lobby, 0, MAXPLAYERS * sizeof(t_player));
	lbb_get_ptr(lobby);
	return (lobby);
}

/* ! ! ! DANGEROUS ! ! ! */
void	*lbb_get_ptr(t_player *new_lobby)
{
	static t_player	*lobby;

	if (new_lobby == NULL)
		return (lobby);
	lobby = new_lobby;
	return (lobby);
}
