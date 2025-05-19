/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:27:55 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/19 18:01:49 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list_fd
{
	int					fd;
	char				*content;
	struct s_list_fd	*next;
}			t_list_fd;

char		*get_substr(char const *s, unsigned int start, size_t len);
t_list_fd	*ft_lstnew_add_back_ptr(int fd, t_list_fd *lst, void *content);
void		ft_lstclear_fd(int fd, t_list_fd **lst, void (*del)(void*));

#endif