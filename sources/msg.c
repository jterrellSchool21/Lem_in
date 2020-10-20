/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:37 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:32 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	msg(int status, t_data *data)
{
	if (status)
		msg_error(status, data);
	else if (data->flags & VERBOSE)
		msg_success(data);
}
