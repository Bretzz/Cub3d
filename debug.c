/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:21:26 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/16 21:51:48 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(char **map)
{
	int	i;

	if (map == NULL)
	{
		ft_printf("(map null)\n");
		return ;
	}
	i = 0;
	while (map[i] != NULL)
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}
