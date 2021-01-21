/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procgo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:29:44 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/21 15:54:09 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int is_op(unsigned char c)
{
    int i;
    int code;

    code = bytecode_to_int(&c, 1);
    i = 0;
    while (i < 16)
    {
        if (table[i].code == code)
            return (i);
        i++;
    }
    return MISTAKESYMB;
}

/*
void node_op(t_field *field, t_process *proc)
{
    int number;

    if ((number = is_op(field->mass[proc->pos].cell)) != MISTAKESYMB)
    {
        
    }
}*/

int countoflivepc(t_field *field)
{
    t_process *head;
    int count;

    count = 0;
    head = field->first;
    if (head != NULL)
    {
        count++;
        head = head->next;
    }
    return (count);
}

void play(t_field *field)
{
    while(countoflivepc(field) > 0)
    {
        field->cycle++;
        //exec or take op code forprocess
        check(field);//проверяет каждый cycle_to_die коретки
    }

}