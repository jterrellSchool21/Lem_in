#include "lemin.h"

int					find_lst_size(t_stk *head)
{
    int i;

    i = 0;
    if (!head)
        return (0);
    while (head)
    {
        i++;
        head = head->next;
    }
    return (i);
}

t_stk				*push(t_stk *head, t_stk *new_head)
{
    if (!head)
    {
        head = new_head;
        head->head = new_head;
        head->next = NULL;
    }
    else
    {
        new_head->next = head;
        new_head->head = new_head;
    }
    return (new_head);
}

t_stk				*remove_elem(t_stk *elem)
{
    t_stk *tmp;
//    t_stk *head;
//
    tmp = elem->next;
////    free(elem);
//    head = tmp;
//    while (tmp)
//    {
//        tmp->head = head;
//        tmp = tmp->next;
//    }
//    elem = head;
    while (tmp)
    {
        if (tmp->next == elem)
            break ;
        tmp = tmp->next;
    }
    if (tmp && tmp->next)
        tmp->next = tmp->next->next;
    elem->next = NULL;
    elem->head = NULL;
    return (elem);
//    return (elem);
}

t_stk				*append_elem(t_stk *stack_head, t_stk *elem)
{
    t_stk *tmp;

    if (stack_head)
    {
        tmp = stack_head;
        while (tmp && tmp->next)
            tmp = tmp->next;
        tmp->next = elem;
        elem->next = NULL;
        elem->head = stack_head->head;
    }
    else
        return (elem);
    return (stack_head);
}