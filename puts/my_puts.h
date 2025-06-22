/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_puts.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:35:24 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/22 13:31:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_PUTS_H
# define MY_PUTS_H

typedef struct s_draw_map
{
	char	digit;
	int		pixel[24][2];
}				t_draw_map;

/* EXTERNALE USE */

void		my_number_put(void *my_struct, int x, int y, int nb);
void		my_string_put(void *my_struct, int x, int y, const char *string);

/* INTERNAL USE */

t_draw_map	get_letter(const char letter);

#endif