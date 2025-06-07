/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:51:32 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/07 09:58:31 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Host Punch main header */

#ifndef HPC_H
# define HPC_H

# include "config.h"
# include "lbb.h"	// for the lobby struct
# include <pthread.h>

/* ============= MULTIPLAYER ============= */

/* CLIENT */

int			client_sender(int servfd, void *buffer, size_t size);

/* SERVER */

int			server_sender(int socket, char *buffer, void *addr, char flag);

/* THE REAL DEAL */

pthread_t	get_me_online(int *index, int *socket, char *ip, char *nickname);

int			hpc_init(void);
int			hpc_free(int *socket, int *index, unsigned long thread);
void		*hpc_mutex(int action);

/* PRINTERS */

void		print_player(t_player player);
void		print_lobby(t_player *lobby);
void		print_quick_lobby(t_player *lobby);

/* BUFFER MESSAGES */

char		*buffer_player_action(t_player player,
				const char *action, void *buffer);
char		*buffer_lobby_action(t_player *lobby,
				const char *action, void *buffer);

/* ENV INTERFACE */

char		**fake_env_init(char *real_env[]);
void		free_fake_env(char **fake_env);

int			make_him_host(char *ip, char **env);
int			set_my_name(char *name, char **env);
int			set_my_ip(char *ip, char **env);

/* USEFUL */

int			is_ip(const char *s);

#endif