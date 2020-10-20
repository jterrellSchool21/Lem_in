/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_short.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:04:06 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:21 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	output_short(t_data *data)
{
	int64_t	i;
	char	buff_name[16];

	i = 0;
	while (++i <= data->n_ants)
	{
		ant_name(i, buff_name);
		buff_fill(buff_name, data);
		buff_fill(data->end_room->name, data);
		buff_fill(" ", data);
	}
	data->buff_line[data->i_buff - 1] = '\n';
	buff_flush(data);
}
