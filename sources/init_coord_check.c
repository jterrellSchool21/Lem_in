/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coord_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:01:57 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:50 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	*transform_crd(void *r)
{
	t_chk_crd	*new;

	if (!(new = malloc(sizeof(t_chk_crd))))
		return (NULL);
	new->crd = ((uint64_t)((t_room*)r)->coord.x << 32) | ((t_room*)r)->coord.y;
	new->r = r;
	return (new);
}

static void	check_crd(t_data *data)
{
	size_t	i;

	i = 0;
	while (++i < data->heap->len)
		if (!cmp_crd(data->heap->data[i], data->heap->data[i - 1]))
		{
			data->error_r = i - 1;
			exit_(DCOORD_ERROR, data);
		}
}

void		init_coord_check(t_data *data)
{
	if (!(data->heap = ar_map(data->rooms, transform_crd, free)))
		exit_(MEMORY_ERROR, data);
	data->heap->cmp = cmp_crd;
	(void)ar_quicksort(data->heap);
	check_crd(data);
	ar_del(&data->heap);
}
