/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_fill_font.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 04:55:27 by totommi           #+#    #+#             */
/*   Updated: 2025/06/21 17:47:21 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int		yft_fill_font(char *monoline, t_font *font);

/* returns the length of the content of the quotes
if the quotes are unclosed, the full length of the string - 1 */
static size_t	get_quotes_len(char *str)
{
	size_t	i;
	char	quotes;

	if (*str != '\'' && *str != '"')
		return (0);
	quotes = *str;
	str++;
	i = 0;
	while (str[i] != '\0' && str[i] != quotes)
		i++;
	return (i);
}

// ".cVoid"
static void	get_color_pair(char *pair_string, t_font *font, int index)
{
	font->table[index].pointer = pair_string[1];
	if (ft_strncmp(VOID_STRING, &pair_string[3], 4) == 0)
	{
		font->table[index].color = VOID;
		return ;
	}
	if (ft_strncmp(FILL_STRING, &pair_string[3], 4) == 0)
	{
		font->table[index].color = FILL;
		return ;
	}
	font->table[index].color = ft_atohexi(&pair_string[3]);
}

static int	get_color_table(char *monoline, int colors,
	t_font *font, size_t *i)
{
	int		count;

	count = 0;
	(*i) = 0;
	while (monoline[(*i)] != '\0' && count < 3)
	{
		if (monoline[(*i)] == '"')
			count++;
		(*i)++;
	}
	if (monoline[--(*i)] != '"')
		return (1);
	count = 0;
	while (monoline[(*i)] != '\0'
		&& (monoline[(*i)] != '}' || monoline[(*i) + 1] != '{'))
	{
		get_color_pair(&monoline[(*i)++], font, count++);
		while (monoline[(*i)] && monoline[(*i)] != '"')
			(*i)++;
		if (++(*i) && (monoline[(*i)] == '\0' || count > colors))
			return (1);
		if (monoline[(*i)++] == '}')
			break ;
	}
	return (0);
}

// {font="MyCoolFont",width=9,heigth=5,[space=3],colors=2,".cVoid","#cFill"}
static int	get_font_format(char *monoline, t_font *font, size_t *i)
{
	const size_t	mono_len = ft_strlen(monoline);
	char			*target;

	ft_strlcpy(font->name, &monoline[7], get_quotes_len(&monoline[6]) + 1);
	target = ft_strnstr(monoline, "heigth=", mono_len);
	if (target == NULL)
		return (1);
	font->heigth = ft_atoi(&target[7]);
	target = ft_strnstr(monoline, "width=", mono_len);
	if (target == NULL)
		return (1);
	font->width = ft_atoi(&target[6]);
	target = ft_strnstr(monoline, "space=", mono_len);
	if (target != NULL)
		font->space = ft_atoi(&target[6]);
	target = ft_strnstr(monoline, "colors=", mono_len);
	if (target == NULL)
		return (1);
	font->colors = ft_atoi(&target[7]);
	if (get_color_table(monoline, font->colors, font, i) != 0)
		return (1);
	return (0);
}

int	yft_fill_font(char *monoline, t_font *font)
{
	size_t			i;

	if (!monoline || !font)
		return (1);
	if (get_font_format(monoline, font, &i) != 0)
		return (2);
	while (monoline[i] != '\0')
	{
		yft_fill_map(&monoline[i], font);
		while (monoline[i] != '}' || monoline[i + 1] != '}')
		{
			if (monoline[i] == '\0')
				return (1);
			i++;
		}
		i += 2;
	}
	return (0);
}
