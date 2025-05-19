/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dropstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:51:52 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/17 16:02:13 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Removes 'len' bytes from the string starting from start */
char	*drop_string(char *str, int start, size_t len)
{
	char		*new_str;
	char		*tar_ptr;
	size_t		i;

	if (str == NULL)
		return (NULL);
	if ((size_t)start > ft_strlen(str))
		return (ft_strdup(str));
	else if (len + start > ft_strlen(str))
		len = ft_strlen(str) - start;
	tar_ptr = &str[start];
	new_str = (char *)ft_calloc(ft_strlen(str) - len + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (&str[i] == tar_ptr)
			str += len;
		new_str[i] = str[i];
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (new_str);
}
