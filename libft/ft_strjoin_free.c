/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:47:31 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/19 17:52:50 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* like ft_strjoin, but with protections over
strlcat and strlcpy, and of course with a free on s1.
intended use: line = ft_strjoin_free(line, new_line). */
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*twelve;
	size_t	size;

	size = 1;
	if (s1 != NULL)
		size += ft_strlen(s1);
	if (s2 != NULL)
		size += ft_strlen(s2);
	twelve = (char *)ft_calloc(size, sizeof(char));
	if (twelve == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strlcpy(twelve, s1, size);
	if (s2 != NULL)
		ft_strlcat(twelve, s2, size);
	free(s1);
	return (twelve);
}
