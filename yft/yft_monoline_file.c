/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_monoline_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 05:07:07 by totommi           #+#    #+#             */
/*   Updated: 2025/06/21 17:24:39 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int	yft_monoline_file(char *file, char **monoline);

static unsigned int	get_actual_length(char *file)
{
	unsigned int	len;
	unsigned int	i;

	len = 0;
	i = 0;
	while (file[i] != '\0')
	{
		if (!ft_isspace(file[i]))
			len++;
		i++;
	}
	return (len);
}

int	yft_monoline_file(char *file, char **monoline)
{
	unsigned int	total;
	size_t			i;
	size_t			s;

	if (!file || !monoline)
		return (1);
	total = get_actual_length(file);
	(*monoline) = (char *)malloc((total + 1) * sizeof(char));
	if ((*monoline) == NULL)
		return (2);
	i = 0;
	s = 0;
	while (file[i] != '\0')
	{
		if (!ft_isspace(file[i]))
			(*monoline)[s++] = file[i];
		i++;
	}
	(*monoline)[s] = '\0';
	return (0);
}
