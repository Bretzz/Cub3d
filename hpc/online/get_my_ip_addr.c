/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_my_addr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:50:12 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/11 01:52:28 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>

char	*get_my_ip_addr(void);

// 'en0' standard wifi
// 'eno2' 42
// 'wlan0' lore
/* gets the eno2 addr of the machine */
char	*get_my_ip_addr(void)
{
	struct ifaddrs		*addrs;
	struct ifaddrs		*tmp;
	struct sockaddr_in	*paddr;
	char				*ip;

	getifaddrs(&addrs);
	tmp = addrs;
	while (tmp)
	{
		if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
		{
			paddr = (struct sockaddr_in *)tmp->ifa_addr;
			if (!ft_strncmp("en0", tmp->ifa_name, 4)
				|| !ft_strncmp("eno2", tmp->ifa_name, 5)
				|| !ft_strncmp("wlan0", tmp->ifa_name, 6))
			{
				ip = inet_ntoa(paddr->sin_addr);
				return (freeifaddrs(addrs), ip);
			}
		}
		tmp = tmp->ifa_next;
	}
	freeifaddrs(addrs);
	return (NULL);
}
