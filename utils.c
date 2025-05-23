/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:55:30 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/23 17:15:09 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim_back_nl(char *str)
{
	size_t	i;

	i = ft_strlen(str) - 1;
	while (str[i] == '\n')
		i--;
	str[++i] = '\0';
	return (str);
}

void	error_msg(char *msg)
{
	write(2, RED, ft_strlen(RED));
	ft_printfd(2, "Error\n");
	ft_printfd(2, "%s\n", msg);
	write(2, RESET, ft_strlen(RESET));
	//clean_exit(mlx); //chiama funzione per liberare tutto
	//exit(1);
}
