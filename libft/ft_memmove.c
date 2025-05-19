/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:18:11 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 16:05:29 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_c;
	unsigned char	*src_c;

	if (!n)
		return (dest);
	dest_c = (unsigned char *)dest;
	src_c = (unsigned char *)src;
	if (dest_c > src_c)
	{
		while (n--)
			dest_c[n] = src_c[n];
	}
	else if (dest_c < src_c)
	{
		while (n--)
			*dest_c++ = *src_c++;
	}
	return (dest);
}
