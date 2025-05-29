/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:51:55 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/29 15:40:13 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <sys/types.h>	// size_t and other stuf
# include <unistd.h>	// NULL

# define MSG_IP_LEN 16		/* len of the ip-string */
# define MSG_NAME_LEN 43	/* len of the name-string */
# define MSG_DATA_LEN 36	/* len of the coord-string */
# define MSG_LEN 132		/* len of the whole msg-string (no action) */

//colors
# define BOLD "\033[1m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

# define LOG "\033[0;36m"
# define WARN "\033[48;5;229m"
# define ERROR "\033[0;41m"
# define STATS "\033[0;34m"
# define KILL "\033[0;101m"
# define LISTEN "\033[0;101m"
# define CONNECT "\033[0;42m"

# define PORT_1 42042
# define PORT_2 41041
# define MAXLINE 2760	/* Max sent/recvd buffer size */

# define MAXPLAYERS 10	/* lbb max number of players */
# define PLAYER_HP 5

#endif