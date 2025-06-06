/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:51:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/06 14:37:30 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Host Punch internal header */

#ifndef HPC_INT_H
# define HPC_INT_H

# include "config.h"
# include "libft.h"
# include "lbb.h"
# include "msg.h"
# include <pthread.h>

/* SENDERS */

int				client_sender(int servfd, void *buffer, size_t size);
int				server_sender(int socket, char *buffer, void *addr, char flag);

/* MUTEX */

void			*hpc_mutex(int action);

/* UTILS */

int				ft_perror(const char *string);
unsigned int	ip_to_uns(const char *ip);

/* PRINTERS */

void			print_player(t_player player);
void			print_lobby(t_player *lobby);
void			print_quick_lobby(t_player *lobby);

/* ENV INTERFACE */

char	    	**fake_env_init(char *real_env[]);
void	    	free_fake_env(char **fake_env);

int				env_is_ready(char *envp[]);
char			*get_locl_ip(char **env);
char			*get_serv_ip(char **env);
char			*get_my_name(char **env);
int				make_him_host(char *ip, char **env);
int				set_my_ip(char *ip, char **env);

/* UTILS */

int				is_ip(const char *s);
void			safeclose(int fd);

#endif