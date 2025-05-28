/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_read_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:11:06 by topiana-          #+#    #+#             */
/*   Updated: 2025/03/21 13:16:20 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg.h"

int	has_pos(const char *msg);
int	has_tar(const char *msg);

int	has_pos(const char *msg)
{
	if (msg[str_skip(msg, 2, ':')] != '\0')
		return (1);
	return (0);
}

int	has_tar(const char *msg)
{
	if (msg[str_skip(msg, 3, ':')] != '\0')
		return (1);
	return (0);
}
