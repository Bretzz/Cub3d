/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:55:30 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 18:51:16 by scarlucc         ###   ########.fr       */
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

void	error_msg(char *msg/* , t_data data */)
{
	printf("Error\n");
	printf("%s\n", msg);
	/* free_map(&data); */ //chiama funzione per liberare tutto
	exit(1);
}
