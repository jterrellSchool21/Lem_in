/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dijkstra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:04:27 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:13 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define LINK(i)		((t_link*)cur_node->links->data[(i)])

static void	prepare_dijkstra(t_data *data)
{
	uint32_t	i;

	i = 0;
	while (i < N_ROOMS)
	{
		ROOM(i)->origin->dist = INT32_MAX;
		ROOM(i)->origin->d_pred = NULL;
		if (!ROOM(i)->is_path)
		{
			ROOM(i)->origin->pred = NULL;
			ROOM(i)->origin->succ = NULL;
		}
		ROOM(i)->is_path = false;
		i++;
	}
	START->origin->dist = 0;
	data->heap->len = 0;
	if (bh_add(data->heap, START->origin))
		exit_(MEMORY_ERROR, data);
}

bool		process_dijkstra(t_data *data)
{
	t_node		*cur_node;
	uint32_t	i;
	int64_t		d;

	prepare_dijkstra(data);
	while ((cur_node = bh_extract(data->heap)))
	{
		i = 0;
		while (i < cur_node->links->len)
		{
			d = (int64_t)cur_node->dist + (int64_t)LINK(i)->w;
			if (d < (int64_t)LINK(i)->n->dist)
			{
				LINK(i)->n->dist = d;
				LINK(i)->n->d_pred = cur_node;
				if (LINK(i)->n == END->origin)
					return (true);
				if (bh_add(data->heap, LINK(i)->n))
					exit_(MEMORY_ERROR, data);
			}
			i++;
		}
	}
	return (false);
}
