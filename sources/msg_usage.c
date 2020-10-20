/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:30 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:33 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	msg_usage(void)
{
	char	*msg;

	msg = "lem-in: undefined combination\ntry 'lem-in -h' for more information";
	ft_dprintf(STDERR_FILENO, "%s\n", msg);
	exit(1);
}
