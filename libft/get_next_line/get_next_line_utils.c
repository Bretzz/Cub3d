/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:19:04 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/16 18:04:07 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*if the third argument is set to '-1' size_t overflows
(taking the full string)*/
char	*get_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		size;
	char		*sub;

	if (start >= ft_strlen(s))
		size = 1;
	else if ((start + len) < ft_strlen(s))
		size = len + 1;
	else
		size = (ft_strlen(s) - start) + 1;
	sub = (char *)malloc(size * sizeof(char));
	sub[size - 1] = '\0';
	if (!sub)
		return (NULL);
	if (start < ft_strlen(s))
	{
		i = 0;
		while (i + 1 < size)
		{
			sub[i] = s[i + start];
			i++;
		}
	}
	return (sub);
}

/*A fusion of ft_lstnew and ft_lstadd_back that returns
	NULL if the mallocation goes wrong,
	a pointer to the new element added if everything goes well.*/
t_list_fd	*ft_lstnew_add_back_ptr(int fd, t_list_fd *lst, void *content)
{
	t_list_fd	*node;

	node = (void *)malloc(1 * sizeof(t_list_fd));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->content = content;
	node->next = NULL;
	if (!lst)
		return (node);
	else if (lst->next == NULL)
		lst->next = node;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = node;
	}
	return (node);
}

/*NOTE: you're expecting to find just one node for each fd
the functions looks for the first fd-node found
if not found leaves everything as it is*/
void	ft_lstclear_fd(int fd, t_list_fd **lst, void (*del)(void*))
{
	t_list_fd	*temp;
	t_list_fd	*nose;
	t_list_fd	*tail;

	if (!lst || !(*lst) || !del)
		return ;
	tail = NULL;
	temp = *lst;
	while (temp && temp->fd != fd)
	{
		tail = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	nose = temp->next;
	(*del)(temp->content);
	free(temp);
	if (tail)
		tail->next = nose;
	else
		*lst = nose;
}
