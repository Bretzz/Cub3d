/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:55:30 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/11 13:08:01 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*trim_back_nl(char *str)
{
	size_t	i;

	if (str[0] == '\n')
		str[0] = '\0';
	if (str[0] == '\0')
		return (str);
	i = ft_strlen(str) - 1;
	while (str[i] == '\n')
		i--;
	if (str[i + 1] == '\n')
		str[++i] = '\0';
	return (str);
}

void	error_msg(char *msg)
{
	write(2, RED, ft_strlen(RED));
	ft_printfd(2, "Error\n");
	ft_printfd(2, "%s\n", msg);
	write(2, RESET, ft_strlen(RESET));
}
