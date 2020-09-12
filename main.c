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

int     counts(int *D, int size)
{
    int     i;
    int     res;

    i = 0;
    res = 0;
    while (i < size)
    {
        if (D[i] != -1)
            res++;
        i++;
    }
    return (res);
}

t_stk   *init_queue()
{
    t_stk   *first;

    if (!(first = malloc(sizeof(t_stk))))
        return (NULL);
    first->next = NULL;
    first->head = NULL;
    return (first);
}

int     empty(t_stk *head)
{
    if (head->num == -1)
        return (1);
    else
        return (0);
}

int     *min_path(t_lem_in *lemin)
{
    int     node;
    int     j;
    int     *D;
    t_stk   *Stack;
    t_stk   *temp;
    int     i;

    D = (int*)ft_memalloc(lemin->count_rooms);
    j = 0;
    while (j < lemin->count_rooms)
        D[j++] = 0;
    Stack = init_queue();
    Stack->num = lemin->start;
//    push(queue);
    i = 0;
    while (!empty(Stack))
    {
        if (i++ == 4)
            break;
        printf("Пустой ли стек - %d\n", empty(Stack));
        printf("Расстояния до точек - ");
        for (int k = 0; k < lemin->count_rooms; k++)
            printf("%d ", D[k]);
        printf("\n");
        printf("Матрица смежности\n");
        print_tab(lemin->matrix, lemin->count_rooms);
        int test2 = Stack->num;
        node = Stack->num;
        remove_elem(Stack);
        if (D[node] == 2)
            continue;
        D[node] = 2;
        j = lemin->count_rooms;
        while (j >= 0)
        {
            int test = lemin->matrix[node][j];
            if (lemin->matrix[node][j] == 1 && D[j] != 2)
            {
                temp = init_queue();
                temp->num = j;
                append_elem(Stack, temp);
                //freeeeeeeeeeeeeeeeeeeeee
                D[j] = 1;
            }
            j--;
            ft_printf("%d\n", node);
        }
    }

//    queue = init_queue();
//    if (!(temp = malloc(sizeof(t_stk))))
//        return (NULL);
//
//    V = (int*)malloc(sizeof(int) * lemin->count_rooms);
//    fill(V, lemin->count_rooms, -1);
//    i = 0;
//    while (i < lemin->count_rooms)
//    {
//        add_to_queue(D, i, i);
//        i++;
//    }
//    j = 0;
//    while (counts(D, lemin->count_rooms) > 0)
//    {
//        i = 0;
//        while (i < lemin->count_rooms)
//        {
//            if (lemin->matrix[j][i] != 0)
//            {
//                temp->num = i;
//                append_elem(queue, temp);
//            }
//        }
//        j++;
//    }
//    return (V);
    return (D);
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
//    int         *res;

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
    solution(lem_in, rooms_array);
//    for (int i = 0; i < lem_in->count_rooms; i++)
//        printf("%d ", res[i]);
    return 0;
}