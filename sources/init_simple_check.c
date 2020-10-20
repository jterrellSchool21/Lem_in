/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simple_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:02:42 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:42 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_simple_check(t_data *data)
{
	if (!data->n_ants)
	{
		if (!(data->flags & OMMIT_ALL))
			if (!(data->flags & OMMIT_INPUT))
				output_input(data);
		if (data->flags & PATHS_NUM)
			show_total_0();
		exit_(OK, data);
	}
	else if (link_exists(START, END))
	{
		if (!(data->flags & OMMIT_ALL))
		{
			if (!(data->flags & OMMIT_INPUT))
				output_input(data);
			output_short(data);
		}
		if (data->flags & PATHS_NUM)
			show_total_1(data);
		exit_(OK, data);
	}
}
