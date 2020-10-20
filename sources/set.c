/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:04:55 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:04 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	path0_del(void *p0)
{
	lst_ht_del((t_lst_ht*)p0, NULL);
}

t_set		*set_new(void)
{
	t_set	*new;

	if (!(new = malloc(sizeof(t_set))))
		return (NULL);
	if (!(new->paths = ar_new(DEFAULT_P, path0_del)))
	{
		free(new);
		return (NULL);
	}
	new->length = 0;
	new->iter = 0;
	new->div = 0;
	new->mod = 0;
	return (new);
}

void		set_del(t_set *s)
{
	if (s)
	{
		ar_del(&s->paths);
		free(s);
	}
}
