/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:09:47 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 16:06:03 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*sdup;
	size_t			size;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s) + 1;
	sdup = (char *)ft_calloc(size, sizeof(char));
	if (sdup == NULL)
		return (NULL);
	ft_strlcpy(sdup, s, size);
	return (sdup);
}
