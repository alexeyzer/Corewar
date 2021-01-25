/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:20:42 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/25 17:17:34 by aguiller         ###   ########.fr       */
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

t_process *for_fork(t_field *field, t_process *parent, int adr)
{
    t_process *res;
    t_process *second;
    int i;

    res = (t_process*)malloc(sizeof(t_process));
    i = 0;
    res->color = parent->color;
    res->idle  = 0;
    res->cop = -1;
    res->lastcyclelive = parent->lastcyclelive;
    res->bytetonextсop = 0;
    res->carry = res->carry;
    res->moved = 1;
    res->pos = adr;
    res->parent = parent -> parent;
    second = field->first;
    second->prev = res;
    res->next = second;
    field->first = res;
    while(i < REG_NUMBER)
    {
        res->reg[i] = parent->reg[i];
        i++; 
    }
    return (res);
}

t_process *createproc(t_champlist *parent, int num)
{
    t_process *res;
    int i;

    i = 1;
    res = (t_process*)malloc(sizeof(t_process));
    res->carry = 0;
    res->pos = (MEM_SIZE / num) * (parent->nowchamp->number - 1);
    res->color = parent->nowchamp->color;
    res->idle = 0;
    res->lastcyclelive = -1;
    res->moved = 1;
    res->cop = -1;
    res->bytetonextсop = 0;
    res->next = NULL;
    res->prev = NULL;
    res->parent = parent;
    res->reg[0] = -1 * parent->nowchamp->number;
    while(i<REG_NUMBER)
    {
        res->reg[i]=0;
        i++;
    }
    return res;
}

t_process *addproc(t_champlist *parent, int num, t_process *head)
{
    t_process *proc;

    proc = createproc(parent, num);
    head->next = proc;
    proc->prev = head;
    return (proc);
}

void init_proc(t_field *field)
{
    if (field->now->nowchamp == NULL)
        field->now = field->now->prev;
    field->first = createproc(field->now,getcountoflist(field->champlist));
    field->current = field->first;
    field->now = field->now->prev;
    while(field->now != NULL)
    {
        if (field->now->nowchamp != NULL)
            field->current = addproc(field->now,
				getcountoflist(field->champlist), field->current);
        field->now = field->now->prev;
    }
}