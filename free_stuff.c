/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:28:48 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/19 18:32:54 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_mtx(void **mtx)
{
	unsigned int	i;

	if (mtx == NULL)
		return ;
	i = 0;
	while (mtx[i] != NULL)
	{
		free(mtx[i]);
		i++;
	}
	free(mtx);
}

void	free_mtx_mtx(void ***mtx)
{
	unsigned int	i;

	if (mtx == NULL)
		return ;
	i = 0;
	while (mtx[i] != NULL)
	{
		free_mtx(mtx[i]);
		i++;
	}
	free(mtx);
}
