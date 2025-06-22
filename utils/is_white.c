/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_white.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-22 14:43:17 by scarlucc          #+#    #+#             */
/*   Updated: 2025-06-22 14:43:17 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_white(char	*line)
{
	int	count;

	count = 0;
	while (line[count])
	{
		if (!ft_isspace(line[count]))
			return (0);
		count++;
	}
	return (1);
}
