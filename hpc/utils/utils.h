/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:00:12 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 21:48:02 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>

int				ft_perror(const char *string);
unsigned int	ip_to_uns(const char *ip);
int				is_ip(const char *s);

int				env_is_ready(char *envp[]);
char			*get_locl_ip(char **env);
char			*get_serv_ip(char **env);
char			*get_my_name(char **env);
// int			make_me_host(char **env);
int				make_him_host(char *ip, char **env);
int				set_my_name(char *name, char **env);
int				set_my_ip(char *ip, char **env);

void 			safeclose(int fd);

#endif