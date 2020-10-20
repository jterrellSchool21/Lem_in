/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:11 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:37 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define CRD(i)	((t_chk_crd*)data->heap->data[(i)])

void	msg_error_rooms_block(t_data *data)
{
	ft_dprintf(STDERR_FILENO, "rooms block not finished\n");
	if (ROOM(N_ROOMS - 1) == START || !START)
		ft_dprintf(STDERR_FILENO, "- %{5}start%{0} room not defined\n");
	if (ROOM(N_ROOMS - 1) == END || !END)
		ft_dprintf(STDERR_FILENO, "- %{5}end%{0} room not defined\n");
	msg_error_last_line(data);
}

void	msg_error_duplicate_room(t_data *data)
{
	int64_t	i;
	char	*name;

	i = data->error_r + 2;
	name = ROOM(data->error_r)->name;
	while (i < N_ROOMS && ft_strequ(ROOM(i)->name, name))
		i++;
	ft_dprintf(STDERR_FILENO, "%d rooms with name %{5}\"%s\"%{0}\n",
		i - data->error_r, name);
}

void	msg_error_duplicate_coord(t_data *data)
{
	int64_t		i;
	uint64_t	coord;

	i = data->error_r + 2;
	coord = CRD(data->error_r)->crd;
	while (i < N_ROOMS && CRD(i)->crd == coord)
		i++;
	ft_dprintf(STDERR_FILENO, "%d rooms with coordinates %{5}(%d, %d)%{0}:\n",
			i - data->error_r, coord >> 32, coord & 0xFFFF);
	while (data->error_r < i)
		ft_dprintf(STDERR_FILENO, "- %{2}\"%s\"%{0}\n",
			CRD(data->error_r++)->r->name);
}

void	msg_error_graph(t_data *data)
{
	ft_dprintf(STDERR_FILENO,
		"no path between %{5}\"%s\"%{0} and %{5}\"%s\"%{0}\n",
			START->name, END->name);
}
