/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:04:14 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:19 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			path_del(void *p)
{
	if (p)
	{
		free(((t_path*)p)->rooms);
		free(((t_path*)p)->ants);
		free(p);
	}
}

static t_path	*path_new(uint32_t n_rooms, uint32_t n_ants)
{
	t_path	*new;

	if (!(new = malloc(sizeof(t_path))))
		return (NULL);
	if (!(new->rooms = malloc(sizeof(t_room*) * (n_rooms + 1))))
	{
		free(new);
		return (NULL);
	}
	if (!(new->ants = (t_ant*)malloc(sizeof(t_ant) * n_ants)))
	{
		path_del(new);
		return (NULL);
	}
	new->n_rooms = n_rooms;
	new->n_ants = n_ants;
	new->n_s_ants = 0;
	new->n_f_ants = 0;
	new->i_ant = 0;
	return (new);
}

void			*path_convert(void *p0)
{
	t_path		*p;
	uint32_t	i;
	t_data		*data;
	uint32_t	n_rooms;
	uint32_t	n_ants;

	data = lst_ht_pop(p0);
	n_rooms = ((t_lst_ht*)p0)->len;
	n_ants = data->best_set->div - n_rooms;
	if (data->best_set->mod > 0)
	{
		n_ants++;
		data->best_set->mod--;
	}
	if (!(p = path_new(n_rooms, n_ants)))
		return (NULL);
	i = 0;
	while (((t_lst_ht*)p0)->len)
		p->rooms[i++] = ((t_node*)lst_ht_pop(p0))->r;
	p->rooms[n_rooms] = END;
	return (p);
}
