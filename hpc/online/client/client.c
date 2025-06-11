/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:02:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/11 13:51:18 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "client.h"

/* The client is a bit trickier. First Binds a socket to
addrin from the SERVER_ONLY... that's it, you talk and
listen from that. */

/* ft_memset(serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr->sin_family = AF_INET;
	serveraddr->sin_port = htons ( MYPORT );
	serveraddr->sin_addr.s_addr = (in_addr_t)inet_addr(servip);
		//192.168.1.5 //INADDR_ANY // ip_to_uns crash on macOS
	lobby[HOST].online = serveraddr; */

/* Dynamically allocated memory of the server
address stored in the HOST slot of the lobby */
static int	set_serv_addr(const char *servip)
{
	t_player *const		lobby = lbb_get_ptr(NULL);
	struct sockaddr_in	*serveraddr;

	serveraddr = malloc(sizeof(struct sockaddr_in));
	if (serveraddr == NULL)
	{
		ft_perror(ERROR"malloc failure"RESET);
		return (-1);
	}
	ft_memset(serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr->sin_family = AF_INET;
	serveraddr->sin_port = htons(PORT_1);
	serveraddr->sin_addr.s_addr = (in_addr_t)inet_addr(servip);
	lbb_mutex(1);
	lobby[HOST].online = serveraddr;
	lbb_mutex(2);
	return (0);
}

/* Binding UDP socket to only receive from MYPORT and
the ip passed.
RETURNS: the bound socket, -1 on error */
static int	bind_to_world(void)
{
	int					servfd;
	struct sockaddr_in	myaddr;

	servfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (servfd < 0)
	{
		ft_perror(ERROR"socket failure"RESET);
		return (-1);
	}
	ft_memset(&myaddr, 0, sizeof(struct sockaddr_in));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(servfd, (struct sockaddr *)&myaddr, sizeof(struct sockaddr)))
	{
		ft_perror(ERROR"bind failure"RESET);
		return (close(servfd), -1);
	}
	return (servfd);
}

/* writing personal NAME and IP into the lobby database */
/* LOBBY MUTEX */
static int	my_data_init(t_player *lobby, char *env[])
{
	if (lobby == NULL)
		return (0);
	lbb_mutex(1);
	if (!lbb_is_alive(lobby[PLAYER]))
	{
		ft_strlcpy(lobby[PLAYER].ip, get_locl_ip(env), 16);
		ft_strlcpy(lobby[PLAYER].name, get_my_name(env), 43);
		lobby[PLAYER].online = get_localhost_addr();
		lobby[PLAYER].data[1] = PLAYER_HP;
	}
	if (DEBUG)
	{
		print_lobby(lobby);
		ft_printf("== = == === = PLAYER COUNT: %u == = == === = \n",
			lbb_player_count());
		ft_printf(LOG">data init ok...%s\n", RESET);
	}	
	lbb_mutex(2);
	return (1);
}

/* returns 0 on error, the socket to write onto.
NOTE: the thread is detached. goes his way */
/* logging:
	ft_printf(LOG">data init ok...%s\n", RESET);
	ft_printf(LOG">ack procedure... (socket %d)%s\n", servfd, RESET);
	ft_printf(LOG">connection approved...%s\n", RESET); */
int	client_routine(pthread_t *tid, char *envp[])
{
	t_player *const	lobby = lbb_get_ptr(NULL);
	int				servfd;

	if (!ft_strcmp("ip-not-found", get_serv_ip(envp)))
	{
		ft_printfd(STDERR_FILENO, ERROR"missing server ip:%s \
env variable not found\n", RESET);
		return (-1);
	}
	if (!my_data_init(lobby, envp))
		return (-1);
	servfd = bind_to_world();
	if (servfd < 0)
		return (-1);
	if (set_serv_addr(get_serv_ip(envp)) < 0)
		return (close(servfd), -1);
	if (client_ack(servfd, lobby) < 0)
		return (close(servfd), -1);
	if (client_receiver(tid, servfd) < 0)
		return (close(servfd), -1);
	return (servfd);
}
