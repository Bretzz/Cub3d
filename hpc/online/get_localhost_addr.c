/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_localhost_addr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:53:31 by totommi           #+#    #+#             */
/*   Updated: 2025/06/11 02:22:34 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "online.h"

struct sockaddr_in	*get_localhost_addr(void)
{
	struct sockaddr_in *const	localhost_addr = malloc(sizeof(struct sockaddr_in));
    
	if (localhost_addr == NULL)
		return (NULL);
	ft_memset(localhost_addr, 0, sizeof(struct sockaddr_in));
    localhost_addr->sin_family = AF_INET;
    localhost_addr->sin_port = htons(PORT_1);
    localhost_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
	return (localhost_addr);
}
