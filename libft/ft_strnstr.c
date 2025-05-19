/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:23:23 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 16:07:16 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	j = 0;
	while (big[i] != '\0' && i < len)
	{
		if (little[j] == '\0')
			break ;
		j = 0;
		while (little[j] && big[i + j] == little[j])
			j++;
		i++;
	}
	if (little[j] == '\0' && (i + j - 1) <= len)
		return ((char *)(big + i - 1));
	return (NULL);
}
