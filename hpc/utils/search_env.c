/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:35:22 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 02:30:15 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_locl_ip(char **env);
char	*get_serv_ip(char **env);
char	*get_my_name(char **env);
int		make_me_host(char **env);
int		make_him_host(char *ip, char **env);
int		set_my_name(char *name, char **env);

/* returns a pointer to the value of the IP var in the env */
char	*get_locl_ip(char **env)
{
	int	i;

	if (env == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp("LOCAL_IP=", env[i], 9) && *(env[i] + 9) != '\0')
			return (env[i] + 9);
		i++;
	}
	return ("ip-not-found");
}

char	*get_serv_ip(char **env)
{
	int	i;

	if (env == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp("SERVER_IP=", env[i], 10) && *(env[i] + 10) != '\0')
			return (env[i] + 10);
		i++;
	}
	return ("ip-not-found");
}

char	*get_my_name(char **env)
{
	int	i;

	if (env == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp("NAME=", env[i], 5) && *(env[i] + 5) != '\0')
			return (env[i] + 5);
		i++;
	}
	return ("no-name");
}

int	make_me_host(char **env)
{
	int	i;

	if (env == NULL)
		return (0);
	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp("SERVER_IP=", env[i], 10) && *(env[i] + 10) != '\0')
		{
			ft_memset(env[i] + 10, 0, ft_strlen(env[i] + 10));
			ft_memmove(env[i] + 10, "host", 4);
			return (1);
		}
		i++;
	}
	return (0);
}

int	make_him_host(char *ip, char **env)
{
	int	i;

	if (ip == NULL || env == NULL)
		return (0);
	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp("SERVER_IP=", env[i], 10) && *(env[i] + 10) != '\0')
		{
			ft_memset(env[i] + 10, 0, ft_strlen(env[i] + 10));
			ft_memmove(env[i] + 10, ip, ft_strlen(ip));
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
		if (!ft_strncmp("NAME=", env[i], 5) && *(env[i] + 5) != '\0')
		{
			ft_memset(env[i] + 5, 0, ft_strlen(env[i] + 5));
			ft_memmove(env[i] + 5, name, ft_strlen(name));
			return (1);
		}
		i++;
	}
	return (0);
}
