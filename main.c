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

int     empty(int *D, int count)
{
    int     i;

    i = 0;
    while (i < count)
    {
        if (D[i] != -1)
            return (0);
        i++;
    }
    return (1);
}

void    add_to_queue(int *queue, int N, int size)
{
    int     i;
    int     *que;

    if (!queue)
    {
        queue = (int*)malloc(sizeof(int) * 1);
        queue[0] = N;
    }
    else
    {
        que = (int*)malloc(sizeof(int) * (size + 1));
        i = 0;
        while (i < size)
        {
            que[i] = queue[i];
            i++;
        }
        que[i + 1] = N;
        *queue = *que;
//        free(que);
    }
}

int     pop_queue(int *queue, int size)
{
    int     tmp;
    int     i;
    int     *que;

    if (queue)
    {
        i = 0;
        que = (int*)malloc(sizeof(int) * size);
        while (i < size)
        {
            if (i == 0)
                tmp = queue[i];
            else
                que[i - 1] = queue[i];
            i++;
        }
        *queue = *que;
//        free(que);
        return (tmp);
    }
    return (-1);
}

void    fill(int *tab, int size, int nbr)
{
    int     i;

    i = 0;
    while (i < size)
    {
        tab[i] = nbr;
        i++;
    }
}

int     *min_path(t_lem_in *lemin)
{
    int     i;
    int     j;
    int     *D; // не посещенные вершины
    int     *V; // посещенные вершины
    int     *queue;
    int     k;

    D = (int*)malloc(sizeof(int) * lemin->count_rooms);
    V = (int*)malloc(sizeof(int) * lemin->count_rooms);
    queue = (int*)malloc(sizeof(int) * lemin->count_rooms);
    fill(queue, lemin->count_rooms, -1);
    i = 0;
    while (i < lemin->count_rooms)
    {
        if (i != lemin->start)
            add_to_queue(D, i, i);
        i++;
    }
    i = lemin->start;
    k = 0;
    while (!empty(D, lemin->count_rooms))
    {
        j = 0;
        while (j < lemin->count_rooms)
        {
            if (lemin->matrix[i][j])
            {
                add_to_queue(queue, j, lemin->count_rooms);
                D[j] = -1;
            }
            j++;
        }
        for(int y = 0; y < lemin->count_rooms; y++)
            printf("%d ", V[y]);
        V[k] = pop_queue(queue, lemin->count_rooms);
        k++;
    }
    return (V);
}

int     *solution(t_lem_in *lemin, t_parsed_room **rooms)
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
    int         *res;

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
//    if(!solution(lem_in, rooms_array))
//        raise_error(3);
    res = solution(lem_in, rooms_array);
    for (int i = 0; i < lem_in->count_rooms; i++)
        printf("%d ", res[i]);
    return 0;
}