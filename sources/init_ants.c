/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:01:53 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:51 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	init_ants(t_data *data)
{
	if (data->n_ants >= 0)
		return (false);
	data->n_ants = get_num(LINE, data);
	return (true);
}
