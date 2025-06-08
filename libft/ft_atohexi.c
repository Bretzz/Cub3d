/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atohexi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:00:51 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/08 17:45:42 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* converts a string into an int.
Skips all the blank spaces, then if the number starts with '0x'
then is treated as an hexadecimal number, if it isn't is treated as
a decimal number (ft_atoi(3)).
RETURNS: the number (int) obtained. */
int	ft_atohexi(const char *nptr)
{
	int			nb;
	const char	base[] = "0123456789abcdef";

	if (nptr == NULL)
		return (0);
	while (ft_strchr(" \f\n\r\t\v", (char)*nptr) && *nptr)
		nptr++;
	if (ft_strncmp("0x", nptr, 2) != 0)
		return (ft_atoi(nptr));
	nptr += 2;
	nb = 0;
	while ((*nptr >= '0' && *nptr <= '9')
		|| (*nptr >= 'a' && *nptr <= 'f'))
	{
		nb = nb * 16 + (ft_strichr(base, *nptr) - 1);
		nptr++;
	}
	return (nb);
}
