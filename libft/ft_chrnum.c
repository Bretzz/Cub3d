/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:02:12 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/19 21:02:24 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* counts how many instances of 'c' in 's'. */
int	ft_chrnum(const char *s, int c)
{
	unsigned int	n;
	size_t			i;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			n++;
		i++;
	}
	return (n);
}
