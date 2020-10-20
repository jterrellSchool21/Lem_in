/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:07 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:38 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	msg_error_no_name1(t_data *data)
{
	ft_dprintf(STDERR_FILENO, "no room with name %{5}\"%s\"%{0}",
		data->words[0]);
	if (!find_room(data->rooms, data->words[1]))
		ft_dprintf(STDERR_FILENO, " neither %{5}\"%s\"%{0}", data->words[1]);
	ft_dprintf(STDERR_FILENO, "\n");
	msg_error_last_line(data);
}

void	msg_error_no_name2(t_data *data)
{
	ft_dprintf(STDERR_FILENO, "no room with name %{5}\"%s\"%{0}\n",
		data->words[1]);
	msg_error_last_line(data);
}

void	msg_error_link_itself(t_data *data)
{
	ft_dprintf(STDERR_FILENO, "can't link to %{5}itself%{0}\n");
	msg_error_last_line(data);
}

void	msg_error_link_exists(t_data *data)
{
	ft_dprintf(STDERR_FILENO, "link already %{5}exists%{0}\n");
	msg_error_last_line(data);
}
