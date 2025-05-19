/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   west_putnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:26:58 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 15:55:12 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	west_putnbr_fd(int fd, int nb)
{
	int		count;
	char	digit;

	count = 0;
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		write(fd, "-", 1);
		count++;
		nb *= -1;
	}
	if (nb >= 10)
		count += west_putnbr_fd(fd, nb / 10);
	digit = (nb % 10) + '0';
	count += west_putchar_fd(fd, digit);
	return (count);
}
