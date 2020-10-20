/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:16 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:36 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		msg_error_last_line(t_data *data)
{
	ft_dprintf(STDERR_FILENO, "%{1}line %d | %{2}\"%s\"%{0}\n",
		data->input->len, LINE);
}

static void	error_message(int status)
{
	char	*msg[4];

	msg[0] = "not enough memory";
	msg[1] = "gnl";
	msg[2] = "i/o error";
	ft_dprintf(STDERR_FILENO, "%{2}%s%{0}\n", msg[-status - 1]);
}

static void	error_function(int status, t_data *data)
{
	void	(*error[14])(t_data*);

	error[NUMBER_ERROR] = msg_error_number;
	error[SROOM_ERROR] = msg_error_start_room;
	error[EROOM_ERORR] = msg_error_end_room;
	error[NAME_ERROR] = msg_error_room_name;
	error[RBLOCK_ERROR] = msg_error_rooms_block;
	error[DROOM_ERROR] = msg_error_duplicate_room;
	error[DCOORD_ERROR] = msg_error_duplicate_coord;
	error[IUNDEF_ERROR] = msg_error_input_udefined;
	error[LNAME1_ERROR] = msg_error_no_name1;
	error[LNAME2_ERROR] = msg_error_no_name2;
	error[LITSELF_ERROR] = msg_error_link_itself;
	error[LEXISTS_ERROR] = msg_error_link_exists;
	error[GRAPH_ERROR] = msg_error_graph;
	error[status](data);
}

void		msg_error(int status, t_data *data)
{
	ft_dprintf(STDERR_FILENO, "Error");
	if (data->flags & VERBOSE)
	{
		ft_dprintf(STDERR_FILENO, ": ");
		if (status < 0)
			error_message(status);
		else
			error_function(status, data);
	}
	else
		ft_dprintf(STDERR_FILENO, "\n");
}
