/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:02 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:39 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	msg_error_number(t_data *data)
{
	if (data->n_ants < 0)
		ft_dprintf(STDERR_FILENO, "number of ants incorrect\n");
	else
		ft_dprintf(STDERR_FILENO, "coordinates incorrect\n");
	msg_error_last_line(data);
}

void	msg_error_start_room(t_data *data)
{
	if (data->start_room)
		ft_dprintf(STDERR_FILENO, "%{5}##start%{0}-command appears twice\n");
	else
		ft_dprintf(STDERR_FILENO,
			"%{5}##start%{0}-command goes straight after %{5}##end%{0}-command"\
			" without end-room being defined\n");
	msg_error_last_line(data);
}

void	msg_error_end_room(t_data *data)
{
	if (data->end_room)
		ft_dprintf(STDERR_FILENO, "%{5}##end%{0}-command appears twice\n");
	else
		ft_dprintf(STDERR_FILENO,
			"%{5}##end%{0}-command straight after %{5}##start%{0}-command"\
			" without start-room being defined\n");
	msg_error_last_line(data);
}

void	msg_error_room_name(t_data *data)
{
	if (data->words[0][0] == 'L')
		ft_dprintf(STDERR_FILENO, "room name can't start with %{5}\"%c\"%{0}-"\
			"character\n", 'L');
	else
		ft_dprintf(STDERR_FILENO, "room name can't contain %{5}\"%c\"%{0}-"\
			"character\n", '-');
	msg_error_last_line(data);
}

void	msg_error_input_udefined(t_data *data)
{
	ft_dprintf(STDERR_FILENO, "input undefined\n");
	msg_error_last_line(data);
}
