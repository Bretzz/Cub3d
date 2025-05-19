/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:30:09 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 16:05:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_c;

	s_c = (unsigned char *)s;
	c = (unsigned char)c;
	i = 0;
	while (s_c[i] != c && i + 1 < n)
		i++;
	if (s_c[i] == c && n != 0)
		return (&s_c[i]);
	return (NULL);
}
