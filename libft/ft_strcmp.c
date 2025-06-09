/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:10:30 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 16:19:06 by scarlucc         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

// #include <stdio.h>

// int	main(void)
// {
// 	char s1[] = "fricky";
// 	char s2[] = "fricky2";

// 	printf("%d\n", ft_strcmp(s1, s2));
// 	return (0);
// }
