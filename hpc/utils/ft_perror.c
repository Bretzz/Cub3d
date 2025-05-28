/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:23:28 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/21 01:09:45 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <string.h>

static char	*ft_strerror(int code)
{
	if (code == 256)
		return ("corrrupted message");
	else if (code == 257)
		return ("lobby not initialized");
	else
		return (strerror(errno));
}

int	ft_perror(const char *string)
{
	ft_printfd(STDERR_FILENO, "%s: %s\n", string, ft_strerror(errno));
	return (errno);
}
