/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:37:31 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 16:04:51 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numalloc(char **str, int n);

static int	ft_numalloc(char **str, int n)
{
	size_t	len;

	len = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	if (n < 0)
		len++;
	*str = (char *)ft_calloc((len + 1), sizeof(char));
	if (*str == NULL)
		return (0);
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	len = ft_numalloc(&str, n);
	if (str == NULL)
		return (NULL);
	if (n == -2147483648)
	{
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	else if (n == 0)
		ft_strlcpy(str, "0", 2);
	else if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		len--;
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
