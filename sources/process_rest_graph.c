/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_rest_graph.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:04:39 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:07 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	restore_node(t_node *origin, t_data *data)
{
	t_array	*tmp;

	((t_link*)origin->links_saved->data[0])->w = 1;
	((t_link*)origin->links_saved->data[1])->w = 1;
	origin->links_saved->len = 0;
	if (PRIMED)
	{
		if (origin->succ != END->origin)
			PRIMED->itself = SUCC->links->data[--(SUCC->links->len)];
		origin->itself = PRIMED->links->data[--(PRIMED->links->len)];
		origin->itself->w = -1;
		tmp = PRIMED->links;
		PRIMED->links = origin->links;
		origin->links = tmp;
	}
	else if (origin->succ != END->origin)
		origin->itself = SUCC->links->data[--(SUCC->links->len)];
}

static void	restore_path(t_data *data)
{
	uint32_t	i;
	t_lst		*l;

	if (!data->prev_set)
		return ;
	i = 0;
	while (i < data->prev_set->paths->len)
	{
		l = ((t_lst_ht*)data->prev_set->paths->data[i])->head;
		while (l)
		{
			restore_node(l->data, data);
			l = l->next;
		}
		i++;
	}
}

void		process_rest_graph(t_data *data)
{
	restore_path(data);
}
