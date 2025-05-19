/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nest_putput_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:05:17 by topiana-          #+#    #+#             */
/*   Updated: 2025/02/26 16:17:48 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	nest_putput_fd(int fd)
{
	write(fd, "%%", 1);
	return (1);
}

/* int main()
{
	nest_putput_fd(1);
	return (0);
} */
