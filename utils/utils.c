/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:55:30 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/20 14:02:58 by scarlucc         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3D.h"

char	*trim_back_nl(char *str)
{
	size_t	i;

	if (str[0] == '\n')
		str[0] = '\0';
	if (str[0] == '\0')
		return (str);
	i = ft_strlen(str) - 1;
	while (str[i] == '\n')
		i--;
	if (str[i + 1] == '\n')
		str[++i] = '\0';
	return (str);
}

void	error_msg(char *msg)
{
	write(2, RED, ft_strlen(RED));
	ft_printfd(2, "Error\n");
	ft_printfd(2, "%s\n", msg);
	write(2, RESET, ft_strlen(RESET));
}
//forse rendere generica anche per carattere sbagliato prima di mappa
void	error_msg2(char *msg, char print_char)
{
	write(2, RED, ft_strlen(RED));
	ft_printfd(2, "Error\n");
	ft_printfd(2, "%s ", msg);
	ft_printfd(2, "'%c'  in map\n", print_char);
	write(2, RESET, ft_strlen(RESET));
}

int	skip_spaces(char	*line, int	count)
{
	while (line[count] == ' ' || line[count] == '\f' || line[count] == '\r'
		|| line[count] == '\t' || line[count] == '\v')
		count++;
	return (count);
}
/* 1 = OK, 0 = error */
int	check_rgb(char	*rgb_value)
{
	int	count;

	count = skip_spaces(rgb_value, 0);
	if (!ft_isdigit(rgb_value[count]))
		return (0);
	while (ft_isdigit(rgb_value[count]))
		count++;
	count = skip_spaces(rgb_value, count);
	if (rgb_value[count] != '\n' && rgb_value[count] != '\0')
		return (0);
	return (1);
}


