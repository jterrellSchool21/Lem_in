/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:02:03 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:49 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_data(t_data *data)
{
	init_prepare(data);
	init_line_process(data, init_ants);
	init_ants_check(data);
	init_line_process(data, init_rooms);
	init_rooms_check(data);
	init_line_process(data, init_links);
	init_simple_check(data);
}
