/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:53:36 by jslave            #+#    #+#             */
/*   Updated: 2020/07/15 18:53:36 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	raise_error(int e)
{
	if (e == 0 || e == 1)
	{
		if (e == 0)
			ft_putstr(">>Malloc error, sorry...\n");
		else if (e == 1)
			ft_putstr(">>No solution\n");
		exit(1);
	}
}

void	free_parsing_structs(t_parsed_room **rooms,
                             t_indexes *indexes, char **data)
{
	int i;

	i = 0;
	if (indexes)
		ft_memdel((void **)&indexes);
	if (data)
		ft_free_2d_array((void **)data);
	if (rooms)
	{
		while (rooms[i])
		{
			if (rooms[i]->conn)
				ft_free_2d_array((void **)rooms[i]->conn);
			if (rooms[i]->name)
				ft_memdel((void **)&rooms[i]->name);
			i++;
		}
		ft_free_2d_array((void **)rooms);
	}
}

void	more_parse_errs(int e)
{
	if (e == 8)
		ft_putstr("start or end room inside paths part\n");
	else if (e == 9)
		ft_putstr("no rooms in the map\n");
	else if (e == 10)
		ft_putstr("non-positive coordinates\n");
	else if (e == 11)
		ft_putstr("bad symbols in map or get_next_line error\n");
	else if (e == 12)
		ft_putstr("the room connected with itself\n");
	else if (e == 13)
		ft_putstr("the same coordinates for two different rooms\n");
	else if (e == 14)
		ft_putstr("comment without comment symbol '#'\n");
	else if (e == 15)
		ft_putstr("room's name can't be named using by first 'L'\n");
}

void	throw_parse_err(int e, t_parsed_room **rooms,
                        t_indexes *indexes, char **data)
{
	ft_putstr("ERROR\n>>Parse error: ");
	if (e == 0)
		ft_putstr("malloc error, sorry...\n");
	else if (e == 1)
		ft_putstr("no indexes to parse in this map.\n");
	else if (e == 2)
		ft_putstr("wrong coordinates of room.\n");
	else if (e == 3)
		ft_putstr("all coordinates have zero values.\n");
	else if (e == 4)
		ft_putstr("non-existed room in paths-part\n");
	else if (e == 5)
		ft_putstr("no ants or non-valid quantity of ants\n");
	else if (e == 6)
		ft_putstr("no start/end room or more one start/end\n");
	else if (e == 7)
		ft_putstr("not finded start/end/paths \n");
	more_parse_errs(e);
	free_parsing_structs(rooms, indexes, data);
	exit(1);
}
