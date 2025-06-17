/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   online.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:04:41 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/17 15:59:22 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ONLINE_H
# define ONLINE_H

//net libraries
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
//# include <sys/types.h>
# include <netdb.h>

# include <pthread.h>

typedef struct s_setup
{
	int		*index;
	int		*socket;
	char	**envp;
}				t_setup;

/* MANAGER */

void				*manager(void *arg);

/* ROUTINES */

int					client_routine(pthread_t *tid, char *envp[]);
int					server_routine(pthread_t *tid, char *envp[]);

/* MSG STRING MANAGEMENT */

int					parse_msg_string(const char *msg);
int					one_player_action(const char *msg,
						t_player *lobby, void *online);
int					cycle_player_msgs(char *msg, t_player *lobby);

char				*buffer_player_action(t_player player,
						const char *action, void *buffer);
char				*buffer_lobby_action(t_player *lobby,
						const char *action, void *buffer);

/* ACK DATA */

void				ack_data_from_msg(const char *msg);
void				ack_data_to_msg(char *buff);

/* DB MANAGEMENT */

// void	new_player(const char *msg, t_player *lobby, void *online);
// void	update_player(const char *msg, t_player *lobby, void *online);
// void	kill_player(const char *msg, t_player *lobby);
// void	host_player(const char *msg, t_player *lobby);
// void	fire_player(const char *msg, t_player *lobby);
// void	hit_player(const char *msg, t_player *lobby);

/* UTILS */

char				*get_my_ip_addr(void);
struct sockaddr_in	*get_localhost_addr(void);

#endif