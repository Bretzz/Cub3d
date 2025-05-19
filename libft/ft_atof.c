/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:16:16 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 15:45:45 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*the functions returns the float value of the number
written on the string after the dot (.). Initially skips all the blank spaces
and numbers so you can use it also at the beginning of the cycle*/
/* ! ! ! INVALI READS ON NUMBERS THAT END WITH A '.' ! ! ! */
static double	ft_get_decimals(const char *nptr)
{
	double	dec;
	size_t	len;

	if (nptr == NULL)
		return (0);
	while (ft_strchr(" \f\n\r\t\v", (char)*nptr) && *nptr)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		nptr++;
	if (*nptr++ != '.')
		return (0);
	len = 0;
	while (nptr[len + 1] >= '0' && nptr[len + 1] <= '9')
		len++;
	dec = 0;
	while (nptr[len] >= '0' && nptr[len] <= '9')
	{
		dec = dec / 10 + (nptr[len] - '0');
		len--;
	}
	return (dec / 10);
}

/* somehow adds a 0.000001 at the end of the number */
double	ft_atof(const char *nptr)
{
	int				sign;
	double			nb;

	if (nptr == NULL)
		return (0);
	while (ft_strchr(" \f\n\r\t\v", (char)*nptr) && *nptr)
		nptr++;
	sign = 1;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	nb = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr == '.')
		nb += ft_get_decimals(nptr);
	return (nb * sign);
}
