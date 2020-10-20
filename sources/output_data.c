/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:46 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:29 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	output_data(t_data *data)
{
	if (!(data->flags & OMMIT_ALL))
	{
		if (!(data->flags & OMMIT_INPUT))
			output_input(data);
		output_prepare(data);
		while (output_line(data))
			;
	}
	if (data->flags & SHOW_PATHS)
		show_paths(data);
	if (data->flags & PATHS_NUM)
		show_total(data);
}
