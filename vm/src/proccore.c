/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgonzo <cgonzo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:20:42 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/20 16:38:11 by cgonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
/*
void revert_list(t_field *field)
{
    t_process *curr;
    t_process *last;

    while(curr)
    {
        
    }
}*/
/*процессы стоят не в том порядке, надо от самого позжего к самому раннему;*/
/*
t_process *for_fork(t_field *field, t_process *parent)
{
    t_process *res;
    int i;

    res = (t_process*)malloc(sizeof(t_process));
    i = 0;
    
    while(i < REG_NUMBER)
    {
        res->reg[i] = parent->reg[i];
        i++; 
    }
    return (res);
}*/

t_process *createproc(t_champlist *parent, int num)
{
    t_process *res;
    int i;

    i = 1;
    res = (t_process*)malloc(sizeof(t_process));
    res->carry = 0;
    res->pos = MEM_SIZE / num * parent->nowchamp->number;
    res->color = parent->nowchamp->color;
    res->idle = 0;
    res->next = NULL;
    res->reg[0] = -1 * parent->nowchamp->number;
    while(i<REG_NUMBER)
    {
        res->reg[i]=0;
        i++;
    }
    return res;
}

void init_proc(t_field *field)
{
    while(field->now != NULL)
    {
        if (field->now->nowchamp != NULL)
        {
            field->current = createproc(field->now,getcountoflist(field->champlist));
            field->current = field->current->next;
        }
        field->now = field->now->prev;
    }
    //revert_list(field);
}