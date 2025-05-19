/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:55 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 15:56:16 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RE_GET_NEXT_LINE_H
# define RE_GET_NEXT_LINE_H

# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list_fd
{
	int					fd;
	char				*str;
	struct s_list_fd	*next;
}			t_list_fd;

t_list_fd	*list_fd_del_fd(int fd, t_list_fd *list);
t_list_fd	*list_fd_add_back(t_list_fd *list, int fd, char *str);
void		list_fd_delone(t_list_fd *node);

#endif