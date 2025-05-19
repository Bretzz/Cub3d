/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nest_putptr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:57:28 by topiana-          #+#    #+#             */
/*   Updated: 2024/12/03 22:57:29 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	nest_putptr_fd(int fd, void *ptr)
{
	int				count;
	char			exa;
	char			*base;
	unsigned long	address;

	base = "0123456789abcdef";
	if (!ptr)
		return (west_putstr_fd(fd, "(nil)"));
	exa = '\0';
	address = (unsigned long)ptr;
	count = 0;
	if (address >= 16)
		count += nest_putptr_fd(fd, (void *)(address / 16));
	exa = base[(address % 16)];
	if (!count)
		count += west_putstr_fd(fd, "0x");
	count += west_putchar_fd(fd, exa);
	return (count);
}
