/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:34:21 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/28 22:35:24 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "server.h"

/* This will be the last thing a secondarry thread will do.
Either the game is over or the host dies. no in between. */

/* So 1 socket bound for INADDR_ANY is all we need. */

/* 
	struct sockaddr_in serveraddr;
    memset( &serveraddr, 0, sizeof(serveraddr) );
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons( 50037 );
    serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );
*/

/* The thread can be detatched, no biggie. */

/* The socket must be usable from the 'minigame'.
(socket + mutex bonus package) */

/* Binds a socket to INADDR_ANY and returns it.
-1 on error */
int	bind_to_port(void)
{
	struct sockaddr_in	anyaddr;
	int					fd;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
	{
		ft_perror(ERROR"socket failure"RESET);
		return (-1);
	}
	ft_memset(&anyaddr, 0, sizeof(anyaddr));
    anyaddr.sin_family = AF_INET;
    anyaddr.sin_port = htons( PORT_1 );
    anyaddr.sin_addr.s_addr = htonl( INADDR_ANY );
	if (bind(fd, (struct sockaddr *)&anyaddr, sizeof(struct sockaddr)) < 0)
	{
		ft_perror(ERROR"bind failure"RESET);
		return (-1);
	}
	return (fd);
}

/* 0 error, 1 all good */
int	my_data_init(t_player *lobby, char *envp[])
{
	if (lobby == NULL)
		return (0);
	ft_strlcpy(lobby[HOST].name, get_my_name(envp), 43);
	ft_strlcpy(lobby[HOST].ip, get_locl_ip(envp), 16);
	print_lobby(lobby);
	ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n", lbb_player_count());
	return (1);
}

/* Retutns the socket to talk to */
int	server_routine(pthread_t *tid, char *envp[])
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	int				socket;

	if (!my_data_init(lobby, envp))
		return (-1);
	socket = bind_to_port();
	// ft_printf(LOG">bound socket to %d%s\n", socket, RESET);
	if (socket < 0)
		return (-1);
	if (server_reciever(tid, socket) < 0)
		return (close(socket), -1);
	return (socket);
	// start server_reciever
	// define server_sender (only way of sending messages) !!! NEED MUTEX !!!
}
