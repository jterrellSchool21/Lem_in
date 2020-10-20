/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:04:42 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:06 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	save_path(t_node *curr, t_data *data)
{
	t_node		*prev;
	t_lst_ht	*path;

	if (!(path = lst_ht_new()))
		exit_(MEMORY_ERROR, data);
	prev = END->origin;
	while (curr != START->origin)
	{
		if (lst_ht_push(path, curr))
		{
			lst_ht_del(path, NULL);
			exit_(MEMORY_ERROR, data);
		}
		curr->r->is_path = true;
		curr->succ = prev;
		prev = curr;
		curr = curr->pred;
	}
	if (ar_add(data->curr_set->paths, path))
	{
		lst_ht_del(path, NULL);
		exit_(MEMORY_ERROR, data);
	}
	data->curr_set->length += path->len;
}

void		process_save_set(t_data *data)
{
	if (!(data->curr_set = set_new()))
		exit_(MEMORY_ERROR, data);
	backtrack(data, save_path);
	save_path(END->origin->d_pred, data);
}

static void	calc_iterations(t_data *data)
{
	uint64_t	sum;

	sum = data->curr_set->length + data->n_ants;
	data->curr_set->div = sum / data->curr_set->paths->len;
	data->curr_set->mod = sum % data->curr_set->paths->len;
	data->curr_set->iter =
		data->curr_set->mod ? data->curr_set->div + 1 : data->curr_set->div;
}

void		process_choose_set(t_data *data)
{
	calc_iterations(data);
	if (data->prev_set != data->best_set)
		set_del(data->prev_set);
	data->prev_set = data->curr_set;
	data->curr_set = NULL;
	if (data->prev_set->iter < data->best_set->iter)
	{
		set_del(data->best_set);
		data->best_set = data->prev_set;
	}
}
