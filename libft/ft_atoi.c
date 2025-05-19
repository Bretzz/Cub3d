/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:49:09 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 16:04:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int				sign;
	int				nb;
	unsigned char	*nptr_c;

	nptr_c = (unsigned char *)nptr;
	while (ft_strchr(" \f\n\r\t\v", (char)*nptr_c) && *nptr_c)
		nptr_c++;
	sign = 1;
	if (*nptr_c == '-')
	{
		sign = -1;
		nptr_c++;
	}
	else if (*nptr_c == '+')
		nptr_c++;
	nb = 0;
	while (*nptr_c >= '0' && *nptr_c <= '9')
	{
		nb = nb * 10 + (*nptr_c - '0');
		nptr_c++;
	}
	return (nb * sign);
}
