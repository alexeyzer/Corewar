/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:53:47 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/25 17:12:18 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champlist *getminbyb(int min, t_champlist *list)
{
    while (list != NULL && list->nowchamp != NULL)
    {
        if (list->nowchamp->number == min)
            return (list);
        list = list->next;
    }
    return (NULL);
}

int findmin(t_champlist *now)
{
    int min;

    if (now == NULL || now->nowchamp == NULL)
        return (MISTAKESYMB);
    min = now->nowchamp->number;
    while (now != NULL && now->nowchamp != NULL)
    {
        if (min > now->nowchamp->number)
            min = now->nowchamp->number;
        now = now->next;
    }
    return (min);
}

void sortlist(t_champlist *list)
{
    t_champ *champ;
    t_champlist *now;
    int i;
    int count;

    count = getcountoflist(list);
    i = 0;
    while (i < count)
    {
        now = list;
        while (now != NULL && now->nowchamp != NULL && now->next\
			!= NULL && now->next->nowchamp != NULL)
        {
            if (now->nowchamp->number > now->next->nowchamp->number)
            {
                champ = now->nowchamp;
                now->nowchamp = now->next->nowchamp;
                now->next->nowchamp = champ;
            }
            now = now->next;
        }
        i++;
    }
}

int getmin(t_field *field)
{
    int min;
    t_champlist *now;
    int nowi;

    nowi = 0;
    min = 1;

    sortlist(field->champlist);
    now = field->champlist;
    while (now != NULL && now->nowchamp != NULL)
    {
        if (min >= now->nowchamp->number)
            min++;
        else
            return (min);
        now = now->next;
    }
    return (MISTAKESYMB);
}

void currectnum(t_field *field)
{
    int min;
    t_champlist *now;
    int nowi;

    nowi = 0;
    min = 1;

    sortlist(field->champlist);
    now = field->champlist;
    while (now != NULL && now->nowchamp != NULL)
    {
        if (min >= (nowi = findmin(now)))
            min++;
        else
        {
            getminbyb(nowi, now)->nowchamp->number = min;
            min++;
        }
        now = now->next;
    }
}