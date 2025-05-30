/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_my_addr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:50:12 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/30 11:28:08 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>

char *get_my_addr(void);

/* gets the eno2 addr of the machine */
char *get_my_addr(void)
{
	struct ifaddrs		*addrs;
	struct ifaddrs		*tmp;
	struct sockaddr_in	*pAddr;
	char				*ip;

	getifaddrs(&addrs);
	tmp = addrs;
	
	while (tmp) 
	{
		if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
		{
			pAddr = (struct sockaddr_in *)tmp->ifa_addr;
			// printf("%s: %s\n", tmp->ifa_name, inet_ntoa(pAddr->sin_addr));
			if (!ft_strncmp("en0", tmp->ifa_name, 4)		// 'en0' standard wifi
				|| !ft_strncmp("eno2", tmp->ifa_name, 5))	// 'eno2' 42
			{
				ip = inet_ntoa(pAddr->sin_addr);
				return (freeifaddrs(addrs), ip);
			}
		}
		tmp = tmp->ifa_next;
	}
	freeifaddrs(addrs);
	return (NULL);
}
