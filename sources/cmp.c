/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:01:35 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:52 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	cmp_dist(void *n1, void *n2)
{
	if (((t_node*)n1)->dist < ((t_node*)n2)->dist)
		return (-1);
	else if (((t_node*)n1)->dist > ((t_node*)n2)->dist)
		return (1);
	else
		return (0);
}

int	cmp_names(void *r1, void *r2)
{
	return (ft_strcmp(((t_room*)r1)->name, ((t_room*)r2)->name));
}

int	cmp_crd(void *crd1, void *crd2)
{
	if (((t_chk_crd*)crd1)->crd < ((t_chk_crd*)crd2)->crd)
		return (-1);
	else if (((t_chk_crd*)crd1)->crd > ((t_chk_crd*)crd2)->crd)
		return (1);
	else
		return (0);
}

int	cmp_links(void *l1, void *l2)
{
	if (((t_link*)l1)->n < ((t_link*)l2)->n)
		return (-1);
	else if (((t_link*)l1)->n > ((t_link*)l2)->n)
		return (1);
	else
		return (0);
}
