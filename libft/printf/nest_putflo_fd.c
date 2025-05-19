/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nest_putflo_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:18:26 by totommi           #+#    #+#             */
/*   Updated: 2025/04/17 15:56:12 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	nest_putdec_fd(int fd, double dec);
static int	nest_putint_fd(int fd, double nbr);

int	nest_putflo_fd(int fd, double nb)
{
	int	count;
	int	dec_count;

	count = 0;
	if (nb >= 2147483648.0f || nb <= -2147483649.0f)
	{
		count += write(fd, "null", 4);
		return (count);
	}
	if (nb < 0)
	{
		count += write(fd, "-", 1);
		nb *= -1;
	}
	count += nest_putint_fd(fd, nb);
	count += write(fd, ".", 1);
	dec_count = nest_putdec_fd(fd, nb);
	while (dec_count < 6)
		dec_count += write(fd, "0", 1);
	count += dec_count;
	return (count);
}

static int	nest_putdec_fd(int fd, double dec)
{
	int		i;
	int		count;
	char	digit;

	count = 0;
	i = 0;
	while (dec - (int)(double)dec > 0 && i < 6)
	{
		dec *= 10;
		digit = ((int)(double)dec % 10) + '0';
		count += write(fd, &digit, 1);
		i++;
	}
	return (count);
}

static int	nest_putint_fd(int fd, double nbr)
{
	int		nb;
	int		count;
	char	digit;

	nb = (int)nbr;
	count = 0;
	if (nb >= 10)
		count += nest_putint_fd(fd, (nb / 10));
	digit = ((int)nb % 10) + '0';
	count += write(fd, &digit, 1);
	return (count);
}
