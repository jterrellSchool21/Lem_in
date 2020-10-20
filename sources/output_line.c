/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:58 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:26 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	move_path(t_path *p, t_data *data)
{
	int32_t	i;

	p->i_ant = p->n_f_ants;
	i = p->n_f_ants;
	while (i < p->n_s_ants)
		if (++p->ants[i++].r == p->n_rooms)
			p->n_f_ants++;
	if (p->n_s_ants < p->n_ants)
	{
		ant_name(++data->best_set->mod, p->ants[p->n_s_ants].name);
		p->ants[p->n_s_ants++].r = 0;
	}
}

static void	move_set(t_data *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->best_set->paths->len)
		move_path(data->best_set->paths->data[i++], data);
}

static bool	get_move(t_path *p, t_data *data)
{
	if (p->i_ant < p->n_s_ants)
	{
		buff_fill(p->ants[p->i_ant].name, data);
		buff_fill(p->rooms[p->ants[p->i_ant].r]->name, data);
		buff_fill(" ", data);
		p->i_ant++;
		return (true);
	}
	return (false);
}

bool		output_line(t_data *data)
{
	uint32_t	i;
	uint32_t	count;
	bool		move;

	count = 0;
	move = true;
	move_set(data);
	while (move)
	{
		move = false;
		if (count < 2)
			count++;
		i = 0;
		while (i < data->best_set->paths->len)
			move |= get_move(data->best_set->paths->data[i++], data);
	}
	if (!move && count == 1)
		return (false);
	data->buff_line[data->i_buff - 1] = '\n';
	buff_flush(data);
	return (true);
}
