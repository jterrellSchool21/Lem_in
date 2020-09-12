/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-validity-utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:59:08 by jslave            #+#    #+#             */
/*   Updated: 2020/07/15 18:59:08 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void    fill_zeros(int **matrix, int size)
{
    int     i;
    int     j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            if (!(matrix[i][j]))
                matrix[i][j] = 0;
            j++;
        }
        i++;
    }
}

int     **print_rooms_array(t_parsed_room **rooms, t_lem_in *lemin) //delete later
{
	int i;
	int j;
	char *type;
    int     **res;

    i = 0;
    res = (int**)ft_memalloc(sizeof(int*) * count_rooms(rooms));
    while (i < count_rooms(rooms))
        res[i++] = (int*)ft_memalloc(sizeof(int) * count_rooms(rooms));
	i = 0;
	printf("PARSER INFO FOR JTERRELL:\n");
	printf("Quantity of ants: %i\n", rooms[0]->ants);
	printf("Quantity of rooms: %i\n", ft_arraylen((void **)rooms));
	printf("Rooms:\n");
	while (rooms[i])
	{
		printf("   name: %s\n", rooms[i]->name);
		printf("   coordinates: x:%i, y:%i\n", rooms[i]->x, rooms[i]->y);
		if (rooms[i]->type == 1)
		{
            lemin->start = ft_atoi(rooms[i]->name);
            type = "start";
        }
		if (rooms[i]->type == 2)
			type = "normal";
		if (rooms[i]->type == 3)
        {
		    lemin->end = i;
            type = "end";
        }
		if(rooms[i]->type == -1)//////////del
			type = "later";//////////
		printf("   type: %s\n", type);
		printf("      connected with rooms: ");
		j = 0;
		if(rooms[i]->conn)
		{

			while((rooms[i]->conn)[j])
			{
			    char *test1 = (rooms[i]->conn)[j];
			    int r = ft_atoi(rooms[i]->name);
			    int c = ft_atoi((rooms[i]->conn)[j]);

                res[ft_atoi(rooms[i]->name)][ft_atoi((rooms[i]->conn)[j])] = 1;
				printf("*%s *", (rooms[i]->conn)[j]);
				j++;
			}

		}
		printf("\n--------\n");
		i++;
	}
    fill_zeros(res, i);
	lemin->count_rooms = i;
	printf("\n");
//	printf("YES\n");
	return (res);
}

int				this_room_is_appeared(char *room, t_parsed_room **rooms)
{
	int i;

	i = 0;
	while (rooms[i])
	{
		if (ft_strcmp(room, rooms[i]->name) == 0)
		{
			if (!rooms[i]->conn)
				return (i);
			else
				return (-5);
		}
		i++;
	}
	return (-1);
}

t_parsed_room	**memory_allocate_for_rooms_array(t_parsed_room **rooms, 
int qnt_rooms)
{
	int i;

	i = 0;
	rooms = (t_parsed_room **)ft_memalloc(sizeof(t_parsed_room *) 
	* (qnt_rooms + 1));
	if (!rooms)
		return (NULL);
	while (i < qnt_rooms)
	{
		rooms[i] = (t_parsed_room *)ft_memalloc(sizeof(t_parsed_room));
		if (!rooms[i])
			return (NULL);
		rooms[i]->ants = -1;
		rooms[i]->x = -1;
		rooms[i]->y = -1;
		rooms[i]->name = NULL;
		rooms[i]->type = -1;
		rooms[i]->conn = NULL;
		i++;
	}
	rooms[i] = NULL;
	return (rooms);
}

int			if_all_coordinates_is_zero(t_parsed_room **rooms)
{
	int i;
	int zeroes;

	zeroes = 0;
	i = 0;
	while (rooms[i])
	{
		if (rooms[i]->x == 0 && rooms[i]->y == 0)
			zeroes++;
		else
			return (0);
		i++;
	}
	if (zeroes == i)
		return (1);
	return (1);
}
