/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:28:39 by totommi           #+#    #+#             */
/*   Updated: 2025/06/08 15:25:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H
# define MSG_H

# include "config.h"
# include "libft.h"

//# include <unistd.h>
# include <ctype.h>
# include <string.h>
# include <strings.h>
# include <stdlib.h>

/* MSG STRING: "NAME:IP:X_Y_Z:X_Y_Z:ACTION" */

/* DATA LENGTH */

size_t	msg_ip_length(const char *msg);
size_t	msg_name_length(const char *msg);

/* GET DATA */

char	*msg_get_name(const char *msg, char *buffer);
char	*msg_get_ip(const char *msg, char *buffer);
int		*msg_get_pos(const char *msg, int *pos);
int		*msg_get_tar(const char *msg, int *tar);

char	*msg_get_pos_tar(const char *msg, char *pos_tar);

/* READ DATA */

int		has_pos(const char *msg);
int		has_tar(const char *msg);

/* UTILS */

int		str_skip(const char *s, int count, int c);
char	*rebuild_coord(int *coord, char *buffer);

#endif