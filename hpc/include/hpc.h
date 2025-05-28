/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:51:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 02:52:20 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Host Punch main header */

#ifndef HPC_H
# define HPC_H

//colors
# define BOLD "\033[1m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

# define LOG "\033[0;36m"
# define WARN "\033[48;5;229m"
# define ERROR "\033[0;41m"
# define STATS "\033[0;34m"
# define KILL "\033[0;101m"
# define LISTEN "\033[0;101m"
# define CONNECT "\033[0;42m"

# include "lbb.h"
# include <pthread.h>

/* ============= MULTIPLAYER ============= */

/* CLIENT */

int			client_sender(int servfd, void *buffer, size_t size);

/* SERVER */

int			server_sender(int socket, char *buffer, void *addr, char flag);

/* THE REAL DEAL */

pthread_t	get_me_online(int *index, int *socket, char *envp[]);

int			hpc_free(int *socket, int *index, void *thread);

/* PRINTERS */

void		print_player(t_player player);
void		print_lobby(t_player *lobby);
void		print_quick_lobby(t_player *lobby);

/* ENV INTERFACE */

int			make_him_host(char *ip, char **env);
int			set_my_name(char *name, char **env);

/* USEFUL STUFF */

int			is_ip(const char *s);

/* ! ! ! TEMPORARY ! ! ! */

char		*get_locl_ip(char **env);
char		*get_serv_ip(char **env);
char		*get_my_name(char **env);


#endif