/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:51:25 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 15:36:00 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	printf_sheriff(int fd, char outlaw, va_list arg);
static int	printf_vice_sheriff(int fd, char outlaw, va_list arg);

/*calls the correct libft function based on what is to be printed
returns 0 if something went wrong
the number of char written if everything was ok
handles: cspdiufxX%*/
static int	printf_sheriff(int fd, char outlaw, va_list arg)
{
	int	shots;

	shots = 0;
	if (outlaw == 'c')
		shots = west_putchar_fd(fd, va_arg(arg, int));
	else if (outlaw == 's')
		shots = west_putstr_fd(fd, va_arg(arg, char *));
	else if (outlaw == 'p')
		shots = nest_putptr_fd(fd, va_arg(arg, void *));
	else if (outlaw == 'd')
		shots = west_putnbr_fd(fd, va_arg(arg, int));
	else if (outlaw == 'i')
		shots = west_putnbr_fd(fd, va_arg(arg, int));
	else if (outlaw == 'u')
		shots = nest_putuns_fd(fd, va_arg(arg, int));
	else if (outlaw == 'x')
		shots = nest_putexa_fd(fd, va_arg(arg, unsigned long), 'x');
	else if (outlaw == 'X')
		shots = nest_putexa_fd(fd, va_arg(arg, unsigned long), 'X');
	else if (outlaw == '%')
		shots = nest_putput_fd(fd);
	else
		shots = printf_vice_sheriff(fd, outlaw, arg);
	return (shots);
}

static int	printf_vice_sheriff(int fd, char outlaw, va_list arg)
{
	int	shots;

	shots = 0;
	if (outlaw == 'f')
		shots = nest_putflo_fd(fd, va_arg(arg, double));
	else if (outlaw == 'z')
		shots = nest_putztr_fd(fd, va_arg(arg, char *), va_arg(arg, int));
	else
		shots = ft_printf("%%%c", outlaw);
	return (shots);
}

//"ciao printo %i"
int	ft_printf(const char *s, ...)
{
	int		the_law;
	va_list	arg;

	if (!s)
		return (-1);
	the_law = 0;
	va_start(arg, s);
	while (*s != '\0')
	{
		if (*s == '%')
		{
			if (*(s + 1) != '\0')
			{
				s++;
				the_law += printf_sheriff(1, *s, arg);
			}
			else
				return (-1);
		}
		else
			the_law += west_putchar_fd(1, *s);
		s++;
	}
	va_end(arg);
	return (the_law);
}

//behaves like fprintf but with fds and not with fd pointers
int	ft_printfd(int fd, const char *s, ...)
{
	int		the_law;
	va_list	arg;

	if (!s)
		return (-1);
	the_law = 0;
	va_start(arg, s);
	while (*s != '\0')
	{
		if (*s == '%')
		{
			if (*(s + 1) != '\0')
			{
				s++;
				the_law += printf_sheriff(fd, *s, arg);
			}
			else
				return (-1);
		}
		else
			the_law += west_putchar_fd(fd, *s);
		s++;
	}
	va_end(arg);
	return (the_law);
}
