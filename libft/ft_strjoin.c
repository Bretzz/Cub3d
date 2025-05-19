/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:22:54 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 16:06:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*twelve;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	twelve = (char *)malloc(size);
	if (twelve == NULL)
		return (NULL);
	ft_strlcpy(twelve, s1, ft_strlen(s1) + 1);
	ft_strlcat(twelve, s2, size);
	return (twelve);
}
