/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:02:37 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:43 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static bool	command(t_data *data)
{
	if (ft_strequ(LINE, "##start"))
	{
		if (!data->start_room && data->end_room != ROOM(N_ROOMS - 1))
			data->start_room = ROOM(N_ROOMS - 1);
		else
			exit_(SROOM_ERROR, data);
	}
	else if (ft_strequ(LINE, "##end"))
	{
		if (!data->end_room && data->start_room != ROOM(N_ROOMS - 1))
			data->end_room = ROOM(N_ROOMS - 1);
		else
			exit_(EROOM_ERORR, data);
	}
	else
		return (false);
	return (true);
}

static char	*get_name(char *str, t_data *data)
{
	if (*str == 'L' || count_ch(str, '-') != 0)
		exit_(NAME_ERROR, data);
	data->words[0] = data->words[2];
	data->words[2] = NULL;
	return (str);
}

static bool	room_line(t_data *data)
{
	if (count_ch(LINE, ' ') != 2)
		return (false);
	if (!(data->words = ft_strsplit(LINE, ' ')))
		exit_(MEMORY_ERROR, data);
	if (count_words(data->words) == 3)
	{
		ROOM(N_ROOMS - 1)->name = get_name(data->words[0], data);
		ROOM(N_ROOMS - 1)->coord.x = get_num(data->words[1], data);
		ROOM(N_ROOMS - 1)->coord.y = get_num(data->words[0], data);
		room_add(data);
		return (true);
	}
	else
		return (false);
}

bool		init_rooms(t_data *data)
{
	if (command(data))
		;
	else if (comment(data))
		;
	else if (room_line(data))
		;
	else
		return (false);
	return (true);
}
