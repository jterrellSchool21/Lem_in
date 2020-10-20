/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_success.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:25 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:34 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	msg_success(t_data *data)
{
	if (data->best_set)
		ft_dprintf(STDOUT_FILENO, "%{5}finished in %d turn%s%{0}\n",
			data->best_set->iter, data->best_set->iter > 1 ? "s" : "");
	else if (data->n_ants > 0)
		ft_dprintf(STDOUT_FILENO, "%{5}finished in 1 turn%{0}\n");
	else
		ft_dprintf(STDOUT_FILENO, "%{5}finished in 0 turns%{0}\n");
}
