/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:12:11 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 15:53:29 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//nlibft.h

int			nest_putexa_fd(int fd, unsigned int nb, char x);
int			nest_putptr_fd(int fd, void *ptr);
int			nest_putput_fd(int fd);
int			nest_putuns_fd(int fd, unsigned int nb);
int			nest_putflo_fd(int fd, double nb);
int			nest_putztr_fd(int fd, char *str, unsigned int len);

//wlibft.h

int			west_putchar_fd(int fd, char c);
int			west_putstr_fd(int fd, char *s);
int			west_putnbr_fd(int fd, int nb);

#endif