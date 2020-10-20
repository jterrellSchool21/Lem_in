/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:02:52 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:40 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link	*link_new(t_node *n, int32_t w)
{
	t_link	*new;

	if (!(new = malloc(sizeof(t_link))))
		return (NULL);
	new->n = n;
	new->w = w;
	return (new);
}

void	link_add(t_room *r1, t_room *r2, int32_t w, t_data *data)
{
	t_link	*new;

	if (!(new = link_new(r2->origin, w)))
		exit_(MEMORY_ERROR, data);
	if (ar_add(r1->origin->links, new))
	{
		free(new);
		exit_(MEMORY_ERROR, data);
	}
}

bool	link_exists(t_room *r1, t_room *r2)
{
	size_t	i;

	i = 0;
	if (r1->origin->links->len > r2->origin->links->len)
		ft_swap_p((void**)&r1, (void**)&r2);
	while (i < r1->origin->links->len)
		if (((t_link*)r1->origin->links->data[i++])->n == r2->origin)
			return (true);
	return (false);
}
