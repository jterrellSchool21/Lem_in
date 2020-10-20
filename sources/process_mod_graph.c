/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_mod_graph.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:04:30 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:12 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_link	*find_link(t_array *ar, t_node *n)
{
	int32_t	left;
	int32_t	right;
	int64_t	middle;

	left = 0;
	right = ar->len - 1;
	while (left <= right)
	{
		middle = (left + right) >> 1;
		if (((t_link*)ar->data[middle])->n == n)
			return (ar->data[middle]);
		else if (((t_link*)ar->data[middle])->n > n)
			right = middle - 1;
		else
			left = middle + 1;
	}
	return (NULL);
}

static void		relink(t_node *origin, t_data *data)
{
	t_array	*tmp;

	if (PRIMED)
	{
		tmp = PRIMED->links;
		PRIMED->links = origin->links;
		origin->links = tmp;
		if (ar_add(PRIMED->links, origin->itself))
			exit_(MEMORY_ERROR, data);
		origin->itself->w = 0;
		origin->itself = NULL;
		if (origin->succ != END->origin)
		{
			if (ar_add(SUCC->links, PRIMED->itself))
				exit_(MEMORY_ERROR, data);
			PRIMED->itself = NULL;
		}
	}
	else if (origin->succ != END->origin)
	{
		if (ar_add(SUCC->links, origin->itself))
			exit_(MEMORY_ERROR, data);
		origin->itself = NULL;
	}
}

static void		mod_node(t_node *origin, t_data *data)
{
	if (ar_add(origin->links_saved, find_link(origin->links, SUCC)))
		exit_(MEMORY_ERROR, data);
	if (ar_add(origin->links_saved, find_link(origin->links, origin->pred)))
		exit_(MEMORY_ERROR, data);
	((t_link*)origin->links_saved->data[0])->w = INT32_MAX;
	((t_link*)origin->links_saved->data[1])->w = INT32_MAX;
	if (origin->links->len > 3)
	{
		if (!PRIMED)
		{
			if (!(PRIMED = node_new(origin->r, 1)))
				exit_(MEMORY_ERROR, data);
			PRIMED->pred = origin;
		}
		PRIMED->dist = INT32_MAX;
		PRIMED->d_pred = NULL;
	}
	relink(origin, data);
}

static void		mod_path(t_node *n, t_data *data)
{
	while (n->pred != START->origin)
	{
		mod_node(n, data);
		n = n->pred;
	}
	mod_node(n, data);
	(find_link(START->origin->links, n))->w = INT32_MAX;
}

void			process_mod_graph(t_data *data)
{
	backtrack(data, mod_path);
}
