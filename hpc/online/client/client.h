/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:03:05 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/09 12:38:09 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

/* instaurate connection -> send signature name:ip -> wait for lobby update -> initialize lobby */
/* split thread that listen from server and updates the struct accordingly */

/* EXPECTED MSG STRINGS FROM SERVER:
'name:ip:pos:tar:action'
NOTE: the semicolons (':') are MANDATORY, even if the fields are empty, e.g: 'pippo:8.8.8.8:::update'
so there will always be at least 4 semicolons in each msg
(future implementation of escapes to protect msg-inflation ;P)*/

/* WARNING: we need to catch the 'we are dead' signal from the 'game' so
that every thread can exit cleanly.*/

# include "../online.h"

/* EXTERNAL USE */

int	client_sender(int servfd, void *buffer, size_t size);
int	client_routine(pthread_t *tid, char *envp[]);

/* INTERNAL USE */

int	client_reciever(pthread_t *tid, int servfd);
#endif 