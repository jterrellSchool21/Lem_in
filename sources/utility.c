/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:05:00 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:00 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	words_del(char ***words)
{
	uint64_t	i;

	i = 0;
	if (*words)
	{
		while ((*words)[i])
			free((*words)[i++]);
		free(*words);
		*words = NULL;
	}
}

void	data_del(t_data *data)
{
	ar_del(&data->rooms);
	set_del(data->best_set);
	set_del(data->curr_set);
	if (data->best_set != data->prev_set)
		set_del(data->prev_set);
	words_del(&data->words);
	lst_ht_del(data->input, free);
	ar_del(&data->heap);
}

void	exit_(int status, t_data *data)
{
	msg(status, data);
	data_del(data);
	exit(status);
}
