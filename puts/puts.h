/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:09:11 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 17:20:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUTS_H
# define PUTS_H

# include <sys/types.h>

struct s_column_vars
{
	unsigned int	put_color;
	float			wall_factor;
	char			*first_y;
	int				height;
	int				y;
};

int		*multiply_array(int *array, size_t size, int factor);
int		*divide_array(int *array, size_t size, int factor);
int		*operation_array(int *array, size_t size, int number, int operator);
float	*operation_arrayf(float *array, size_t size,
			float number, int operator);

#endif