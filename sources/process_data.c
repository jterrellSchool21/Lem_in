/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:04:22 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:14 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	process_data(t_data *data)
{
	process_prepare(data);
	while (process_bhandari(data))
	{
		if (data->best_set->iter == min_iter(data))
			break ;
	}
	if (!data->prev_set)
		exit_(GRAPH_ERROR, data);
}
