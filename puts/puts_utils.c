/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:08:29 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/09 19:21:30 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* tiny utils pt.2 */
int	*multiply_array(int *array, size_t size, int factor)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		array[i] *= factor;
		i++;
	}
	return (array);
}

/* tiny utils pt.2 */
int	*divide_array(int *array, size_t size, int divisor)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		array[i] /= divisor;
		i++;
	}
	return (array);
}

/* tiny utils pt.2 */
int	*operation_array(int *array, size_t size, int number, int operator)
{
	unsigned int	i;

	i = 0;
	if (operator == '+')
	{
		while (i < size)
			array[i++] += number;
	}
	else if (operator == '-')
	{
		while (i < size)
			array[i++] -= number;
	}
	else if (operator == '*')
	{
		while (i < size)
			array[i++] *= number;
	}
	else if (operator == '/')
	{
		while (i < size)
			array[i++] /= number;
	}
	return (array);
}

float	*operation_arrayf(float *array, size_t size, float number, int operator)
{
	unsigned int	i;

	i = 0;
	if (operator == '+')
	{
		while (i < size)
			array[i++] += number;
	}
	else if (operator == '-')
	{
		while (i < size)
			array[i++] -= number;
	}
	else if (operator == '*')
	{
		while (i < size)
			array[i++] *= number;
	}
	else if (operator == '/')
	{
		while (i < size)
			array[i++] /= number;
	}
	return (array);
}
