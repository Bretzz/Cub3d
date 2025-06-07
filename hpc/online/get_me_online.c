/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_me_online.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:15:22 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/07 19:17:33 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hpc_int.h"
#include "online.h"

pthread_t	get_me_online(int *index, int *socket, char *ip, char *nickname);

/* initialize variables based on data */
static int	data_init(int *socket, int *index, char *envp[])
{
	char *const	servip = get_serv_ip(envp);

	if (!socket || !index || !envp)
		return (0);
	*socket = 0;
	if (!ft_strcmp("host", servip))
		*index = 0;
	else if (is_ip(servip))
		*index = 1;
	else
		return (0);
	return (1);
}

/* setups the fake_env with the NAME and SERVER_IP variables
initialized. */
static char	**setup_fake_env(char *ip, char *nickname)
{
	char **const	fenvp = fake_env_init(NULL);

	if (fenvp == NULL)
		return (NULL);
	set_my_ip(get_my_addr(), fenvp);
	set_my_name(nickname, fenvp);
	make_him_host(ip, fenvp);
	return (fenvp);
}

/* checks weather 'ip' and 'nickname' are valid params:
ip is an actual IP address, nickname is less than
42 chars and doesn't contain '\n' or ':'. */
static int	parse_input(char *ip, char *nickname)
{
	if (!ip || (!is_ip(ip) && ft_strcmp("host", ip)))
		return (0);
	if (!nickname || ft_strlen(nickname) > 42 || ft_strchr(nickname, '\n')
		|| ft_strchr(nickname, ':'))
		return (0);
	return (1);
}

/* Spawns the manager thread for internet connection.
Switches from client to host on kill, and changes host
if the host died. If the socket pointed by *socket gets
close(3)d, the thread starts the cleanup routine.
RETURNS: the thread to join before shutting down  */
/* HOW IT WORKS:
	1. reads the index,
	2. starts the routine & sets the socket
	3. (something changes)
		3.1 we died? return : go to 1
NOTE: the 'envp' will be free'd as a custom matrix pointer,
meaning evey single 'sring' will be individually free'd, before
freeint the 'envp' pointer itself. */
pthread_t	get_me_online(int *index, int *socket, char *ip, char *nickname)
{
	pthread_t	tid;
	t_setup		*setup;
	char		**fenvp;

	if (!parse_input(ip, nickname))
		return ((pthread_t)0);
	fenvp = setup_fake_env(ip, nickname);
	if (fenvp == NULL)
		return ((pthread_t)0);
	setup = malloc(sizeof(t_setup));
	if (setup == NULL)
		return ((pthread_t)0);
	setup->index = index;
	setup->socket = socket;
	setup->envp = fenvp;
	if (!data_init(socket, index, fenvp))
		return (free_fake_env(fenvp), free(setup), (pthread_t)0);
	if (pthread_create(&tid, NULL, &manager, setup) < 0)
	{
		ft_perror(ERROR"thread launch"RESET);
		return (free_fake_env(fenvp), free(setup), (pthread_t)0);
	}
	while (hpc_mutex(1) && *socket == 0 && hpc_mutex(2))
		usleep(1000);
	return (hpc_mutex(2), tid);
}
