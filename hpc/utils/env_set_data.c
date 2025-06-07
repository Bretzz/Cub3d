/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 00:37:06 by totommi           #+#    #+#             */
/*   Updated: 2025/06/08 00:38:03 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"

// int		make_me_host(char **env);
int		make_him_host(char *ip, char **env);
int		set_my_name(char *name, char **env);
int		set_my_ip(char *ip, char **env);

// int	make_me_host(char **env)
// {
// 	int	i;

// 	if (env == NULL)
// 		return (0);
// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		if (!ft_strncmp("SERVER_IP=", env[i], 10) && *(env[i] + 10) != '\0')
// 		{
// 			ft_memset(env[i] + 10, 0, ft_strlen(env[i] + 10));
// 			ft_memmove(env[i] + 10, "host", 4);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	make_him_host(char *ip, char **env)
{
	int	i;

	if (ip == NULL || env == NULL)
		return (0);
	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp("SERVER_IP=", env[i], 10))
		{
			ft_memset(env[i] + 10, 0, ft_strlen(env[i] + 10));
			ft_memmove(env[i] + 10, ip, ft_strlen(ip) + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	set_my_name(char *name, char **env)
{
	int	i;

	if (name == NULL || env == NULL)
		return (0);
	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp("NAME=", env[i], 5))
		{
			ft_memset(env[i] + 5, 0, ft_strlen(env[i] + 5));
			ft_memmove(env[i] + 5, name, ft_strlen(name) + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	set_my_ip(char *ip, char **env)
{
	int	i;

	if (ip == NULL || env == NULL)
		return (0);
	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp("LOCAL_IP=", env[i], 9))
		{
			ft_memset(env[i] + 9, 0, ft_strlen(env[i] + 9));
			ft_memmove(env[i] + 9, ip, ft_strlen(ip) + 1);
			return (1);
		}
		i++;
	}
	return (0);
}
