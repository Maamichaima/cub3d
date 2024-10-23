/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:36:45 by maamichaima       #+#    #+#             */
/*   Updated: 2024/10/21 15:42:54 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

t_garbage *ft_lstnew_garbage(void *content)
{
    t_garbage *l;

    if (!content)
        return (NULL);
    l = malloc(sizeof(t_garbage));
    if (!l)
        return (NULL);
    l->p = content;
    l->next = NULL;
    return (l);
}

t_garbage *ft_lstlast_garbage(t_garbage *lst)
{
    if (lst == NULL)
        return (NULL);
    while (lst->next != NULL)
        lst = lst->next;
    return (lst);
}

void ft_lstadd_back_garbage(t_garbage **lst, t_garbage *new)
{
    t_garbage *t;

    if (!lst || !new)
        return;
    if (*lst == NULL)
        *lst = new;
    else
    {
        t = ft_lstlast_garbage(*lst);
        t->next = new;
    }
}

void *ft_malloc(int size, char c)
{
    static t_garbage *head;
    t_garbage *tmp;
    void *ptr;

    if(c == 'f')
    {
        while(head)
        {
            tmp = head;
            head = head->next;
            free(tmp->p);
            free(tmp);
        }
        head = NULL;
        return NULL;
    }
    else
    {
        ptr = malloc(size);
        ft_lstadd_back_garbage(&head, ft_lstnew_garbage(ptr));
    }
    return ptr;
}
