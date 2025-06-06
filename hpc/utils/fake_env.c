/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:30:43 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/06 14:46:31 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"

char	**fake_env_init(char *real_env[]);
void	free_fake_env(char **fake_env);

/* freeing the dud. */
void	free_fake_env(char **fake_env)
{
	unsigned int	i;

	i = 0;
	while (fake_env[i] != NULL)
	{
		if (!ft_strncmp("NAME=", fake_env[i], 5))
			free(fake_env[i]);
		else if (!ft_strncmp("SERVER_IP=", fake_env[i], 10))
			free(fake_env[i]);
		else if (!ft_strncmp("LOCAL_IP=", fake_env[i], 9))
			free(fake_env[i]);
		i++;
	}
	free(fake_env);
}

/* initialize an env with NAME, SERVER_IP, LOCAL_IP.
if 'real_env' isn't null, copies the whole matrix. */
char	**fake_env_init(char *real_env[])
{
	char			**fake_env;
	size_t			real_len;
	unsigned int	i;

	real_len = 0;
	if (real_env != NULL)
		real_len = ft_mtxlen((void **)real_env);
	fake_env = (char **)ft_calloc((real_len + 4), sizeof(char *));
	if (fake_env == NULL)
		return (NULL);
	i = 0;
	while (i < real_len)
	{
		fake_env[i] = real_env[i];
		i++;
	}
	fake_env[i++] = ft_strdup("NAME=really-long-name-that-isnt-set-in-any-mean");
	fake_env[i++] = ft_strdup("LOCAL_IP=ip-not-set-but-long-enough");
	fake_env[i++] = ft_strdup("SERVER_IP=ip-not-set-but-long-enough");
	if (fake_env[real_len] == NULL
		|| fake_env[real_len + 1] == NULL
		|| fake_env[real_len + 2] == NULL)
	{
		free(fake_env[real_len]);
		free(fake_env[real_len + 1]);
		free(fake_env[real_len + 2]);
		free(fake_env);
		return (NULL);
	}
	return (fake_env);
}
