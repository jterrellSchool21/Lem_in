/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:54 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:27 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	output_input(t_data *data)
{
	char	*line;

	while ((line = lst_ht_pop(data->input)))
	{
		buff_fill(line, data);
		buff_fill("\n", data);
		free(line);
	}
	buff_fill("\n", data);
	buff_flush(data);
	ft_memdel((void**)&data->input);
}
