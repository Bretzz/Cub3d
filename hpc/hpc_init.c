/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:26:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/08 16:23:14 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"

// ft_printf(GREEN"DEBUG %d%s\n", DEBUG, RESET);
/* call this befor get_me_online */
int	hpc_init(void)
{
	if (lbb_init() == NULL)
		return (1);
	hpc_mutex(0);
	lbb_mutex(0);
	return (0);
}
