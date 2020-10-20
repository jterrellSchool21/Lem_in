/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:02:21 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:46 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*find_room(t_array *ar, char *name)
{
	int32_t	cmp;
	int32_t	left;
	int32_t	right;
	int64_t	middle;

	left = 0;
	right = ar->len - 1;
	while (left <= right)
	{
		middle = (left + right) >> 1;
		if ((cmp = ft_strcmp(name, ((t_room*)ar->data[middle])->name)) == 0)
			return (ar->data[middle]);
		else if (cmp < 0)
			right = middle - 1;
		else
			left = middle + 1;
	}
	return (NULL);
}

static void	link_rooms(t_room *r1, t_room *r2, t_data *data)
{
	if (!link_exists(r1, r2))
	{
		link_add(r1, r2, 1, data);
		link_add(r2, r1, 1, data);
	}
	else if (!(data->flags & IGNORE_LINKS))
		exit_(LEXISTS_ERROR, data);
}

static bool	link_line(t_data *data)
{
	t_room	*r1;
	t_room	*r2;

	if (count_ch(LINE, ' ') != 0 || count_ch(LINE, '-') != 1)
		exit_(IUNDEF_ERROR, data);
	if (!(data->words = ft_strsplit(LINE, '-')))
		exit_(MEMORY_ERROR, data);
	if (count_words(data->words) == 2)
	{
		if (!(r1 = find_room(data->rooms, data->words[0])))
			exit_(LNAME1_ERROR, data);
		if (!(r2 = find_room(data->rooms, data->words[1])))
			exit_(LNAME2_ERROR, data);
		if (r1 == r2)
			exit_(LITSELF_ERROR, data);
		link_rooms(r1, r2, data);
		return (true);
	}
	else
		return (false);
}

bool		init_links(t_data *data)
{
	if (comment(data))
		;
	else if (link_line(data))
		;
	else
		exit_(IUNDEF_ERROR, data);
	return (true);
}
