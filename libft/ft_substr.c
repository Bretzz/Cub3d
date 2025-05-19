/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:29:01 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 16:07:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*if the third argument is set to '-1' size_t overflows
(taking the full string)*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (start >= ft_strlen(s))
		return ((char *)ft_calloc(1, sizeof(char)));
	else if ((start + len) < ft_strlen(s))
		size = len + 1;
	else
		size = (ft_strlen(s) - start) + 1;
	sub = (char *)ft_calloc(size, sizeof(char));
	if (!sub)
		return (NULL);
	if (start < ft_strlen(s))
		ft_strlcpy(sub, &s[start], size);
	return (sub);
}
