/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bhandari.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:04:18 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:15 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define D_PRED_PRIMED	(curr->d_pred->r->primed == curr->d_pred)

static void	fix_relations(t_data *data)
{
	t_node	*curr;

	curr = END->origin->d_pred;
	while (curr != START->origin)
	{
		if (D_PRED_PRIMED)
		{
			if (curr != curr->d_pred->pred)
				curr->pred = curr->d_pred->pred;
		}
		else if (!curr->pred && curr != curr->d_pred->pred)
			curr->pred = curr->d_pred;
		else
			curr->d_pred->pred = NULL;
		curr = curr->d_pred;
	}
}

bool		process_bhandari(t_data *data)
{
	process_mod_graph(data);
	if (!process_dijkstra(data))
		return (false);
	process_rest_graph(data);
	fix_relations(data);
	process_save_set(data);
	process_choose_set(data);
	return (true);
}
