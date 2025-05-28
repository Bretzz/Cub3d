/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:44:58 by totommi           #+#    #+#             */
/*   Updated: 2025/05/28 01:29:22 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LBB_H
# define LBB_H

# define HOST 0
# define PLAYER 1

# ifndef MAXPLAYERS
#  define MAXPLAYERS 10
# endif

# include "libft.h"
# include "msg.h"

typedef struct s_player
{
	char	name[MSG_NAME_LEN + 1];	// max name length: 42
	char	ip[MSG_IP_LEN + 1];		//max ip length: 15
	int		pos[3];
	int		tar[3];
	char	pos_tar[MSG_DATA_LEN * 2 + 1];
	void	*online;	// ptr to other stuff
}				t_player;

/* PORTABLE POINTER */

void	*lbb_get_ptr(t_player *new_lobby);

/* BASICS */

void	*lbb_init(void);

/* DATA MEASUREMENT */

size_t	lbb_name_length(const char *name);
size_t	lbb_ip_length(const char *ip);

/* READ DATA */ /* obtaining information about the database */

int		lbb_get_index(const char *msg);
int		lbb_next_free_slot(void);
int		lbb_is_alive(t_player player);
size_t	lbb_player_count(void);

/* WRITE DATA */ /* writing data into the database */

int		lbb_add_player(const char *msg);
int		lbb_update_player(const char *msg);
void	*lbb_kill_player(const char *msg);
void	*lbb_move_player(int src, int dest);
void	lbb_push_up(void);

/* GET DATA */ /* writing data from the database into a buffer */

char	*lbb_get_full_stats(t_player player, void *buffer);
char	*lbb_get_lobby_stats(t_player *lobby, void *buffer);

/* LBB to MSG */

void	*lbb_to_msg(t_player player);

/* CLEANUP */

void	lbb_delete_lobby(t_player *lobby);

#endif