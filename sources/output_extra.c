/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:50 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:28 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		show_total_0(void)
{
	ft_dprintf(STDOUT_FILENO, "TOTAL: paths not needed\n\n");
}

void		show_total_1(t_data *data)
{
	ft_dprintf(STDOUT_FILENO,
		"\nTOTAL: inf paths from %{5}%s%{0} to %{5}%s%{0} of length 0\n\n",
		START->name, END->name);
}

void		show_total(t_data *data)
{
	ft_dprintf(STDOUT_FILENO,
		"\nTOTAL: %d path%s from %{5}%s%{0} to %{5}%s%{0}\n",
		data->best_set->paths->len, data->best_set->paths->len > 1 ? "s" : "",
		data->start_room->name, data->end_room->name);
}

static void	show_path(t_path *p)
{
	int64_t	i;

	i = 0;
	ft_dprintf(STDOUT_FILENO, "%d room%s, ", p->n_rooms,
		p->n_rooms > 1 ? "s" : "");
	ft_dprintf(STDOUT_FILENO, "%d ant%s\n", p->n_ants,
		p->n_ants > 1 ? "s" : "");
	while (i < p->n_rooms)
	{
		ft_dprintf(STDOUT_FILENO, "%{1}[%{3}%s%{1}]%{0}",
			p->rooms[i]->name);
		if (i < p->n_rooms - 1)
			ft_dprintf(STDOUT_FILENO, "%{1}-->%{0}");
		i++;
	}
	ft_dprintf(STDOUT_FILENO, "\n");
}

void		show_paths(t_data *data)
{
	int64_t	i;

	i = 0;
	while (i < data->best_set->paths->len)
	{
		ft_dprintf(STDOUT_FILENO, "\n%{2}PATH %d:%{0} ", i + 1);
		show_path(data->best_set->paths->data[i++]);
	}
	ft_dprintf(STDOUT_FILENO, "\n");
}
