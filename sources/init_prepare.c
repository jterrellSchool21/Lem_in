/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:02:26 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:45 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	prepare_rooms(t_data *data)
{
	if (!(data->rooms = ar_new(DEFAULT_R, room_del)))
		exit_(MEMORY_ERROR, data);
	data->rooms->cmp = cmp_names;
	room_add(data);
}

static void	prepare_input(t_data *data)
{
	if (!(data->input = lst_ht_new()))
		exit_(MEMORY_ERROR, data);
}

void		init_prepare(t_data *data)
{
	prepare_rooms(data);
	prepare_input(data);
	data->n_ants = -1;
	data->start_room = NULL;
	data->end_room = NULL;
	data->best_set = NULL;
	data->curr_set = NULL;
	data->prev_set = NULL;
	data->words = NULL;
	data->error_r = 0;
	data->i_buff = 0;
	data->heap = NULL;
}
