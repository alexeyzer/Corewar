/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgonzo <cgonzo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:36:56 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/19 17:30:13 by cgonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champlist *isitbusy(t_champlist *head, int number)
 {
    while (head != NULL)
    {
        if (head->nowchamp->number == number)
            return (head);
        head = head->next;
    }
    return (NULL);
 }
 t_field        *init()
 {
    t_field *field;
    int i;

    i = 0;
    field =  (t_field*)malloc(sizeof(t_field));
    field->champlist = (t_champlist*)malloc(sizeof(t_champlist));
    field->champlist->next = NULL;
    field->champlist->sorted = 0;
    field->champlist->nowchamp = NULL;
    field->counter = 0;
    field->now = field->champlist;
    while(i < MEM_SIZE)
    {
        field->mass[i].color = 'z';
         field->mass[i].cell = 0x00;
        i++;
    }
    return (field);
 }

 t_champlist *addchamtolist(t_champlist *now)
 {
    t_champlist *newlist;

    newlist = (t_champlist*)malloc(sizeof(t_champlist));
    newlist->next = NULL;
    newlist->nowchamp = NULL;
    now->next = newlist;
    now->sorted = 0;
    now = now->next;
    return (now);
 }
 