/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:59:35 by jslave            #+#    #+#             */
/*   Updated: 2020/07/15 18:59:35 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_lem_in	*ft_init_lem_in(void)
{
	t_lem_in	*lemin;

	if (!(lemin = (t_lem_in *)ft_memalloc(sizeof(t_lem_in))))
        raise_error(0);
	lemin->ants = 0;
	lemin->commands = (char**)malloc(sizeof(char*) * 10);
	lemin->comments = (char**)malloc(sizeof(char*) * 10);
	lemin->rooms = NULL;
	lemin->cmd = 0;
	lemin->cmt = 0;
	lemin->ants = NULL;
	lemin->matrix = NULL;
	return (lemin);

}

int     count_rooms(t_parsed_room **rooms)
{
    int     i;

    i = 0;
    while (rooms[i])
    {
        i++;
    }
    return (i);
}

void    print_tab(int **tab, int size)
{
    int     i;
    int     j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            printf("%d ", tab[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

//int     **make_tab(t_parsed_room **rooms)
//{
//    int     i;
//    int     j;
//
//    while (rooms[i])
//    {
//        j = 0;
//        if(rooms[i]->conn)
//        {
//            while((rooms[i]->conn)[j])
//            {
//                printf("%s ", (rooms[i]->conn)[j]);
//                res[i][j] = ft_atoi((rooms[i]->conn)[j]);
//                j++;
//            }
//
//        }
//        else
//            res[i][j] = 0;
//        printf("\n--------\n");
//        i++;
//    }
////    print_tab(res, count_rooms(rooms));
//    return (res);
//}

int     nulls(int *D, int count)
{
    int     i;

    i = 0;
    while (i < count)
    {
        if (D[i] != 0)
            return (0);
        i++;
    }
    return (1);
}

void    add_to_queue(int *queue, int N)
{

}

void    pop_queue()
{

}

int     min_path(t_lem_in *lemin)
{
    int     i;
    int     j;
    int     *D; // не посещенные вершины
    int     *V; // посещенные вершины
    int     *queue;
    int     *

    D = (int*)malloc(sizeof(int) * lemin->count_rooms);
    V = (int*)malloc(sizeof(int) * lemin->count_rooms);
    i = 0;
    while (i < lemin->count_rooms)
    {
        if (i != lemin->start)
            D[i] = i;
        else
            D[i] = 0;
        i++;
    }
    i = lemin->start;
    while (!nulls(D, lemin->count_rooms))
    {
        j = 0;
        while (j < lemin->count_rooms)
        {
            if (lemin->matrix[i][j])
            {
                add_to_queue(queue, j);
            }
            j++;
        }
        pop_queue();
    }
}

int     solution(t_lem_in *lemin, t_parsed_room **rooms)
{
//    return (0);
    return (min_path(lemin));
//    Suurballe()
}

int main(int argc, char **argv)

{
	char		*line;
	t_lem_in	*lem_in;
    char *line_result;
    int lines;
    t_parsed_room  **rooms_array;

    lines = 0;
    line_result = ft_strnew(1);
	while ((get_next_line(0, &line)) > 0)
	{
	    line = ft_strjoinfree_both(line,ft_strdup( "\n"));
	    line_result = ft_strjoinfree_both(line_result, line);
        lines++;
	}
    char **array_for_validity_check = ft_strsplit(line_result,'\n');
    ft_memdel((void **) &line_result);
    rooms_array = check_validity_of_input_data(array_for_validity_check, lines);
    lem_in = ft_init_lem_in();
    lem_in->matrix = print_rooms_array(rooms_array, lem_in);
    free_parsing_structs(rooms_array, NULL, NULL);//DELETE later but freee rooms by this func only
    print_tab(lem_in->matrix, lem_in->count_rooms);
    if(!solution(lem_in, rooms_array))
        raise_error(3);

    return 0;
}