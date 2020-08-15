/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-validity-main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:58:48 by jslave            #+#    #+#             */
/*   Updated: 2020/07/15 18:58:48 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		fill_room_by_line(char *data, t_parsed_room *room)
{
	char	**splited_line;
	char	*trimed;
	int		err;

	err = 1;
	trimed = ft_strtrim(data);
	splited_line = ft_strsplit(trimed, ' ');
	if (ft_arraylen((void **)splited_line) == 3)
	{
		if (splited_line[0][0] == 'L')
			err = -15;
		else
			room->name = ft_strdup(splited_line[0]);
		room->x = ft_atoi_long_long(splited_line[1]);
		room->y = ft_atoi_long_long(splited_line[2]);
		if (room->x < 0 || room->y < 0 || room->x > INT_MAX || 
		room->y > INT_MAX)
			err = -2;
	}
	else
		err = -2;
	ft_memdel((void **)&trimed);
	ft_free_2d_array((void **)splited_line);
	return (err);
}

int				fill_rooms_name_and_coords(char **data, t_indexes *indexes, 
t_parsed_room **rooms_array)
{
	int i;
	int rooms_iter;
	int err;

	rooms_iter = 0;
	i = 1;
	while (i < indexes->paths && data[i])
	{
		if (data[i][0] != '#')
		{
			err = fill_room_by_line(data[i], rooms_array[rooms_iter]);
			if (err < 0)
				throw_parse_err((err * -1), rooms_array, indexes, data);
			(rooms_array[rooms_iter])->ants = indexes->ants;
			(rooms_array[rooms_iter])->type = 2;

			if (i == indexes->start_room)
				(rooms_array[rooms_iter])->type = 1;
			else if (i == indexes->end_room)
				(rooms_array[rooms_iter])->type = 3;
			rooms_iter++;
		}
		i++;
	}
	return (i);
}


void			print_map_and_free_parse_structs(t_indexes *indexes, 
char **data)
{
	int i;

	i = 0;
	while (data && data[i])
	{
		printf("%s\n", data[i]);
		i++;
		if (i == ft_arraylen((void **)data))
			printf("\n");
	}
	ft_free_2d_array((void **)data);
	ft_memdel((void **)&indexes);
}


int				coordinates_is_repeated(t_parsed_room **rooms_array)
{
	int i;
	int j;

	i = 0;
	while (rooms_array[i])
	{
		j = 0;
		while (rooms_array[j])
		{
			if (i != j)
			{
				if (rooms_array[i]->x == rooms_array[j]->x && 
				rooms_array[i]->y == rooms_array[j]->y)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


t_parsed_room	**check_validity_of_input_data(char **data, int lines)
{
	int					i;
	t_parsed_room		**rooms_array;
	t_indexes			*indexes;

	if (ft_arraylen((void **)data) != lines)
		throw_parse_err(11, NULL, NULL, data);
	indexes = find_indexes_to_parse(data, indexes);
	if (!(rooms_array = memory_allocate_for_rooms_array(rooms_array, 
	indexes->rooms)))
		throw_parse_err(1, NULL, indexes, data);
	i = fill_rooms_name_and_coords(data, indexes, rooms_array);
	fill_connections_for_rooms(i, rooms_array, data, indexes);
	check_connections_for_rooms(rooms_array, data, indexes);
	if (if_all_coordinates_is_zero(rooms_array) == 1)
		throw_parse_err(3, rooms_array, indexes, data);
	if (coordinates_is_repeated(rooms_array))
		throw_parse_err(13, rooms_array, indexes, data);
	print_map_and_free_parse_structs(indexes, data);
//	print_rooms_array(rooms_array);//delete later
	return (rooms_array);
}
