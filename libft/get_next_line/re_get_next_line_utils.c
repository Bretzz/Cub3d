/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:29:16 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 15:54:01 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "re_get_next_line.h"
#include "libft.h"

t_list_fd	*list_fd_del_fd(int fd, t_list_fd *list);
t_list_fd	*list_fd_add_back(t_list_fd *list, int fd, char *str);
void		list_fd_delone(t_list_fd *node);

void	list_fd_delone(t_list_fd *node)
{
	free(node->str);
	free(node);
}

t_list_fd	*list_fd_add_back(t_list_fd *list, int fd, char *str)
{
	t_list_fd	*node;
	t_list_fd	*head;

	node = (t_list_fd *)malloc(1 * sizeof(t_list_fd));
	if (node == NULL)
		return (list);
	node->fd = fd;
	node->str = str;
	node->next = NULL;
	if (list == NULL)
		return (node);
	head = list;
	while (list->next)
		list = list->next;
	list->next = node;
	return (head);
}

t_list_fd	*list_fd_del_fd(int fd, t_list_fd *list)
{
	t_list_fd		*temp[2];

	if (list == NULL)
		return (NULL);
	temp[0] = list;
	if (temp[0]->fd == fd)
	{
		list = list->next;
		list_fd_delone(temp[0]);
		return (list);
	}
	while (temp[0])
	{
		if (temp[0]->next && temp[0]->next->fd == fd)
		{
			temp[1] = temp[0]->next;
			temp[0]->next = temp[0]->next->next;
			list_fd_delone(temp[1]);
		}
		temp[0] = temp[0]->next;
	}
	return (list);
}
