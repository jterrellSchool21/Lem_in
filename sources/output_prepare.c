/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_prepare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:04:02 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:22 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	prepare_set(t_data *data)
{
	t_array		*p;
	uint32_t	i;

	i = 0;
	while (i < data->best_set->paths->len)
		lst_ht_push(data->best_set->paths->data[i++], data);
	if (!(p = ar_map(data->best_set->paths, path_convert, path_del)))
		exit_(MEMORY_ERROR, data);
	ar_del(&data->best_set->paths);
	data->best_set->paths = p;
}

void		output_prepare(t_data *data)
{
	ar_del(&data->heap);
	prepare_set(data);
}
