/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_one_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <scarlucc@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:26:49 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/18 19:26:23 by scarlucc         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/



#include "cub3D.h"

int just_one_player(char **map);

/* counts how many chars of the set are in the string */
static int  strset_count(const char *str, const char *set)
{
    size_t  i;
    int     count;

    if (!str || !set)
        return (-1);
    count = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (ft_strchr(set, str[i]))
            count++;
        i++;
    }
    return (count);
}

/* returns the number of chars found in any
string of 'mtx' that are inside 'map'. */
static int  mapset_count(char **mtx, const char *set)
{
    int     count;
    int     i;

    if (!mtx || !set)
        return (-1);
    count = 0;
    i = 0;
    while (mtx[i] != NULL)
    {
        count += strset_count(mtx[i], set);
        i++;
    }
    return (count);
}

/* returns 0 if one player is found, 1 if
0 or more than 1 are found. */
int just_one_player(char **map)
{
    const int   p_count = mapset_count(map, "NSEW");

    if (p_count == 1)
        return (0);
    return (1);
}