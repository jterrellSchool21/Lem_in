/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-validity-connections_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:58:19 by jslave            #+#    #+#             */
/*   Updated: 2020/07/15 18:58:19 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	*create_string_with_connections(char *conn, t_parsed_room **rooms, 
t_parsed_room *curr_room)
{
	int i;
	int k;

	i = 0;
	while (rooms[i])
	{
		k = 0;
		while (rooms[i]->conn && (rooms[i]->conn)[k])
		{
			if (ft_strcmp(rooms[i]->conn[k], curr_room->name) == 0)
			{
				conn = ft_strjoinfree_s2(rooms[i]->name, conn);
				conn = ft_strjoinfree_both(ft_strdup(","), conn);
			}
			k++;
		}
		i++;
	}
	return (conn);
}

void	check_connections_for_rooms(t_parsed_room **rooms, char **data, 
t_indexes *indexes)//del data and indexes&????
{
	int		j;
	char	*connections;

	connections = ft_strdup("");
	j = 0;
	while (rooms[j])
	{
		if (!rooms[j]->conn)
		{
			if (connections = create_string_with_connections(connections, 
			rooms, rooms[j]))
			{
				rooms[j]->conn = ft_strsplit(connections, ',');
				ft_memdel((void **)&connections);
			}
		}
		j++;
	}
	if (connections)
		ft_memdel((void **)&connections);
}

int		increment_index(t_parsed_room *room, char **splited_line, int ind)
{
	if (splited_line[1] && splited_line[0])
	{
		if (ft_strcmp(room->name, splited_line[1]) == 0)
		{
			room->conn[ind] = ft_strdup(splited_line[0]);
			ind++;
		}
		else if (ft_strcmp(room->name, splited_line[0]) == 0)
		{
			room->conn[ind] = ft_strdup(splited_line[1]);
			ind++;
		}
	}
	return (ind);
}
void	create_connections_for_this_room(t_parsed_room *room, int j, 
char **data, int size)
{
	int		ind;
	char	*trimed;
	char	**splited_line;

	ind = 0;
	room->conn = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	while (data[j] && ind < size)
	{
		trimed = ft_strtrim(data[j]);
		splited_line = ft_strsplit(trimed, '-');
		ind = increment_index(room, splited_line, ind);
		ft_memdel((void **)&trimed);
		ft_free_2d_array((void **)splited_line);
		j++;
	}
	room->conn[ind] = NULL;
}
