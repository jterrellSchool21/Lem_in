/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-validity-connections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:57:49 by jslave            #+#    #+#             */
/*   Updated: 2020/07/15 18:57:49 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_errors_for_current_line_path(char *datai, char *dataj,
                                              t_parsed_room **rooms_array, t_indexes *indexes)///del indexes????
{
	char	*trimed;
	char	**splited_line;
	char	*trimed2;
	char	**splited_line2;
	int		err;

	err = 0;
	trimed = ft_strtrim(datai);
	splited_line = ft_strsplit(trimed, '-');
	trimed2 = ft_strtrim(dataj);
	splited_line2 = ft_strsplit(trimed2, '-');
	if (trimed2 && splited_line2[0] && splited_line2[1])
	{
		if (this_room_is_appeared(splited_line2[1], rooms_array) == -1 || 
		this_room_is_appeared(splited_line2[0], rooms_array) == -1)
			err = -4;
		else if (ft_strcmp(splited_line2[0], splited_line2[1]) == 0)
			err = -12;
		else if (ft_strcmp(splited_line2[1], splited_line[0]) == 0 || 
		ft_strcmp(splited_line2[0], splited_line[0]) == 0)
			err = 1;
	}
	ft_memdel((void **)&trimed);
	ft_free_2d_array((void **)splited_line);
	ft_memdel((void **)&trimed2);
	ft_free_2d_array((void **)splited_line2);
	return (err);
}


int		calculate_ind(char *data, t_parsed_room **rooms_array)
{
	char	**splited_line;
	char	*trimed;
	int		ind;

	ind = -1;
	trimed = ft_strtrim(data);
	splited_line = ft_strsplit(trimed, '-');
	if (trimed && splited_line && splited_line[0])
		ind = this_room_is_appeared(splited_line[0], rooms_array);
	if (trimed)
		ft_memdel((void **)&trimed);
	if (splited_line)
		ft_free_2d_array((void **)splited_line);
	return (ind);
}

void	calculate_needed_size(char **data, int i, t_parsed_room **rooms_array,
                              t_indexes *indexes)
{
	int		needed_size;
	int		j;
	int		test;
	int		ind;

	j = indexes->paths;
	needed_size = 0;
	while (data[j])
	{
		test = check_errors_for_current_line_path(data[i], 
		data[j], rooms_array, indexes);
		if (test < 0)
			throw_parse_err(test * (-1), rooms_array, indexes, data);
		needed_size += test;
		j++;
	}
	if (needed_size)
	{
		ind = calculate_ind(data[i], rooms_array);
		if (ind)
			create_connections_for_this_room(rooms_array[ind], 
			indexes->paths, data, needed_size);
	}
}

void	fill_connections_for_rooms(int i, t_parsed_room **rooms_array,
                                   char **data, t_indexes *indexes)
{
	int		ind;
	char	**splited_line;
	char	*trimed;
	int		len;

	len = 0;
	while (data[i])
	{
		if (data[i][0] != '#')
		{
			trimed = ft_strtrim(data[i]);
			splited_line = ft_strsplit(trimed, '-');
			len = ft_arraylen((void **)splited_line);
			ind = this_room_is_appeared(splited_line[0], rooms_array);
			ft_memdel((void **)&trimed);
			ft_free_2d_array((void **)splited_line);
			if (ind != -1 && ind != -5 && len == 2)
				calculate_needed_size(data, i, rooms_array, indexes);
			else if (ind == -1)
				throw_parse_err(4, rooms_array, indexes, data);
		}
		i++;
	}
}
