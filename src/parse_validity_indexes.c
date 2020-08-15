/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-validity-indexes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:58:32 by jslave            #+#    #+#             */
/*   Updated: 2020/07/15 18:58:32 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			find_start_end_commented_indexes(char **data, 
t_indexes *indexes)
{
	int i;

	i = 1;
	while (data[i])
	{
		if (data[i][0] == '#')
			indexes->commented_lines++;
		if (ft_strcmp(data[i], "##start") == 0)
		{
			if (indexes->start_room != -1 || data[i + 1] == NULL)
				throw_parse_err(6, NULL, indexes, data);
			indexes->start_room = i + 1;
			i++;
		}
		else if (ft_strcmp(data[i], "##end") == 0)
		{
			if (indexes->end_room != -1 || data[i + 1] == NULL)
				throw_parse_err(6, NULL, indexes, data);
			indexes->end_room = i + 1;
			i++;
		}
		i++;
	}
}

void			find_path_index(char **data, t_indexes *indexes)
{
	int		i;
	char	**next_line;

	i = 1;
	while (data[i])
	{
		if (ft_strstr(data[i], "-") != NULL && data[i][0] != '#')
		{
			if (data[i + 1] && data[i + 1][0] != '#')
			{

				next_line = ft_strsplit(data[i + 1], ' ');
				if (ft_arraylen((void **)next_line) == 3)
				{
					ft_free_2d_array((void **)next_line);
					throw_parse_err(10, NULL, indexes, data);
				}
				ft_free_2d_array((void **)next_line);
			}
			if (indexes->paths == -1)
				indexes->paths = i;
			indexes->paths_count++;
		}
		i++;
	}
}

t_indexes	*find_indexes(char **data, t_indexes *indexes)
{
	int		i;
	char	**next_line;

	if (!(indexes = (t_indexes *)ft_memalloc(sizeof(t_indexes))))
		throw_parse_err(1, NULL, indexes, data);
	i = 1;
	indexes->end_room = -1;
	indexes->start_room = -1;
	indexes->paths = -1;
	indexes->commented_lines = 0;
	indexes->paths_count = 0;
	indexes->ants = 0;
	if (ft_is_int(data[0]) == 1)
		indexes->ants = ft_atoi(data[0]);
	if (indexes->ants <= 0)
		throw_parse_err(5, NULL, indexes, data);
	find_path_index(data, indexes);
	find_start_end_commented_indexes(data, indexes);
	if (indexes->paths == -1 || indexes->start_room == -1 || 
	indexes->end_room == -1)
		throw_parse_err(7, NULL, indexes, data);
	if (indexes->start_room >= indexes->paths || 
	indexes->end_room >= indexes->paths)
		throw_parse_err(8, NULL, indexes, data);
	return (indexes);
}

int				check_data_for_bad_comments(char **data)
{
	int		i;
	char	*trimed;
	char	**splited_sp;
	char	**splited_min;
	int		res;

	res = 0;
	i = 1;
	while (data[i])
	{
		if (data[i][0] != '#' && ft_strlen(data[i]))
		{
			trimed = ft_strtrim(data[i]);
			splited_sp = ft_strsplit(trimed, ' ');
			splited_min = ft_strsplit(trimed, '-');
			if (ft_arraylen((void **)splited_min) == 1 
			&& ft_arraylen((void **)splited_sp) == 1)
				res = 1;
			ft_memdel((void **)&trimed);
			ft_free_2d_array((void **)splited_sp);
			ft_free_2d_array((void **)splited_min);
		}
		i++;
	}
	return (res);
}

t_indexes	*find_indexes_to_parse(char **data, t_indexes *indexes)
{
	if (check_data_for_bad_comments(data) == 1)
		throw_parse_err(14, NULL, NULL, data);
	indexes = find_indexes(data, indexes);
	if (!indexes)
		throw_parse_err(1, NULL, indexes, data);
	indexes->rooms = ft_arraylen((void **)data) - 1 - indexes->commented_lines
	- indexes->paths_count;
	if (!indexes->rooms)
		throw_parse_err(9, NULL, indexes, data);
	return (indexes);
}
