/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nest_putexa_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:56:51 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/26 16:17:39 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	nest_putexa_fd(int fd, unsigned int nb, char x)
{
	int			count;
	char		exa;
	char		*base_low;
	char		*base_upp;

	base_low = "0123456789abcdef";
	base_upp = "0123456789ABCDEF";
	exa = '\0';
	count = 0;
	if (nb >= 16)
		count += nest_putexa_fd(fd, nb / 16, x);
	if (x == 'x')
		exa = base_low[(nb % 16)];
	else if (x == 'X')
		exa = base_upp[(nb % 16)];
	else
		return (west_putstr_fd(fd, "Wrong flag passed to 'putexa'\n"));
	count += west_putchar_fd(fd, exa);
	return (count);
}
