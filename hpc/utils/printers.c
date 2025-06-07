/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:31:53 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/08 00:35:16 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lbb.h"
#include "libft.h"

void	print_player(t_player player);
void	print_lobby(t_player *lobby);
void	print_quick_lobby(t_player *lobby);

void	print_player(t_player player)
{
	char		buffer[MSG_LEN];

	if (!lbb_is_alive(player))
		ft_printf("(empty slot) %p %p\n", player.online, player.extra);
	else
	{
		ft_printf("%s ", lbb_get_full_stats(player, buffer));
		ft_printf("%p %p", player.online, player.extra);
		ft_printf("\n");
	}
}

void	print_quick_lobby(t_player *lobby)
{
	char	buffer[MSG_LEN];
	int		i;

	i = 0;
	while (i < MAXPLAYERS)
	{
		if (lbb_is_alive(lobby[i]))
			ft_printf("%s\n", lbb_get_full_stats(lobby[i], buffer));
		i++;
	}
}

void	print_lobby(t_player *lobby)
{
	int	i;

	ft_printf(CYAN"\n");
	i = 0;
	while (i < MAXPLAYERS)
	{
		print_player(lobby[i]);
		i++;
	}
	ft_printf("%s\n", RESET);
}
