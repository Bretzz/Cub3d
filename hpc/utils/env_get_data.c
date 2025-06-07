/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:35:22 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/08 00:37:59 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

int		env_is_ready(char *envp[]);
char	*get_locl_ip(char **env);
char	*get_serv_ip(char **env);
char	*get_my_name(char **env);

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
