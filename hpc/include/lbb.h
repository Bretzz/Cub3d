/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:44:58 by totommi           #+#    #+#             */
/*   Updated: 2025/05/28 22:22:23 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LBB_H
# define LBB_H

# include "config.h"
# include <stdlib.h>	// malloc and free

# define HOST 0		/* lbb host index */
# define PLAYER 1	/* lbb player index */

# ifndef MAXPLAYERS
#  define MAXPLAYERS 10	/* lbb max number of players */
# endif

typedef struct s_player
{
	char	name[MSG_NAME_LEN];	// max name length: 42
	char	ip[MSG_IP_LEN];		//max ip length: 15
	int		pos[3];
	int		tar[3];
	char	pos_tar[MSG_DATA_LEN * 2];
	int		shoot;
	void	*online;			// ptr to other stuff
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