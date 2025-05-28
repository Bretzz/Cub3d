/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:45:10 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 14:04:31 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg.h"

int		str_skip(const char *s, int count, int c);
char	*rebuild_coord(int *coord, char *buffer);

/* return the index of the first char after 'count'
instances of 'c' in 's'. */
int	str_skip(const char *s, int count, int c)
{
	int	skip;

	skip = 0;
	while (s[skip] != '\0' && count > 0)
	{
		if (s[skip] == c)
			count--;
		skip++;
	}
	return (skip);
}

/* expected buffsize >MSG_DATA_LEN */
char	*rebuild_coord(int *coord, char *buffer)
{
	char	*coord_itoa[3];
	int		i;

	if (buffer == NULL)
		return (NULL);
	ft_memset(buffer, 0, MSG_DATA_LEN);
	if (coord == NULL)
		return (buffer);
	coord_itoa[0] = ft_itoa(coord[0]);
	coord_itoa[1] = ft_itoa(coord[1]);
	coord_itoa[2] = ft_itoa(coord[2]);
	if (!coord_itoa[0] || !coord_itoa[1] || !coord_itoa[2])
		return (free(coord_itoa[0]), free(coord_itoa[1]),
			free(coord_itoa[2]), buffer);
	i = 0;
	while (i < 3)
	{
		ft_strlcat(buffer, coord_itoa[i],
			ft_strlen(buffer) + ft_strlen(coord_itoa[i]) + 1);
		if (i != 2)
			ft_strlcat(buffer, "_", ft_strlen(buffer) + 2);
		i++;
	}
	return (free(coord_itoa[0]), free(coord_itoa[1]),
		free(coord_itoa[2]), buffer);
}
