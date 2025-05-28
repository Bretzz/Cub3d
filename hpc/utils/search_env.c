/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:35:22 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 19:35:17 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

int		env_is_ready(char *envp[]);
char	*get_locl_ip(char **env);
char	*get_serv_ip(char **env);
char	*get_my_name(char **env);
// int		make_me_host(char **env);
int		make_him_host(char *ip, char **env);
int		set_my_name(char *name, char **env);
int		set_my_ip(char *ip, char **env);

/* checks if the enviroment contains NAME, LOCAL_IP, SERVER_IP 
and they are initialized*/
int	env_is_ready(char *envp[])
{
	char			found[3];
	unsigned int	i;

	if (envp == NULL)
		return (0);
	ft_memset(found, 0, 3 * sizeof(char));
	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp("NAME=", envp[i], 5) && *(envp[i] + 5) != '\0')
			found[0] = 1;
		else if (!ft_strncmp("SERVER_IP=", envp[i], 10)
			&& (!ft_strncmp("host", envp[i] + 10, 4) || is_ip(envp[i] + 10)))
			found[1] = 1;
		else if (!ft_strncmp("LOCAL_IP=", envp[i], 9)
			&& is_ip(envp[i] + 9))
			found[2] = 1;
		i++;
	}
	if (found[0] && found[1] && found[2])
		return (1);
	return (0);
}

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
		if (!ft_strncmp("SERVER_IP=", env[i], 10)/*  && *(env[i] + 10) != '\0' */)
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
		if (!ft_strncmp("NAME=", env[i], 5)/*  && *(env[i] + 5) != '\0' */)
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
		if (!ft_strncmp("LOCAL_IP=", env[i], 9)/*  && *(env[i] + 9) != '\0' */)
		{
			ft_memset(env[i] + 9, 0, ft_strlen(env[i] + 9));
			ft_memmove(env[i] + 9, ip, ft_strlen(ip) + 1);
			return (1);
		}
		i++;
	}
	return (0);
}
