/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:16:08 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/08 14:43:11 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

void	new_player(const char *msg, t_player *lobby, void *online);
void	update_player(const char *msg, t_player *lobby, void *online);
void	kill_player(const char *msg, t_player *lobby);
void	host_player(const char *msg, t_player *lobby);
void	fire_player(const char *msg, t_player *lobby);
void	hit_player(const char *msg, t_player *lobby);

#endif