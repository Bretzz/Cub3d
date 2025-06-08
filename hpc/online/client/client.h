/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:03:05 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/08 15:03:00 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

/* ROUTINE:
    1. instaurate connection
    2. send signature name:ip
    3. wait for lobby update
    4. initialize lobby */
/* split thread that listen from server and updates the struct accordingly */

/* EXPECTED MSG STRINGS FROM SERVER:
'name:ip:pos:tar:action'
NOTE: the semicolons (':') are MANDATORY,
even if the fields are empty, e.g: 'pippo:8.8.8.8:::update'
so there will always be at least 4 semicolons in each msg
(future implementation of escapes to protect msg-inflation ;P)*/

/* WARNING: we need to catch the 'we are dead' signal from the 'game' so
that every thread can exit cleanly.*/

# include "../online.h"

/* EXTERNAL USE */

int	client_sender(int servfd, void *buffer, size_t size);
int	client_routine(pthread_t *tid, char *envp[]);

/* INTERNAL USE */

int	client_receiver(pthread_t *tid, int servfd);
int	client_ack(int servfd, t_player *lobby);

#endif 