/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_p1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:23:33 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/24 17:56:05 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void isindex(t_field *field, int nbr)
{
    t_champlist *now;

    now = field->champlist;
    while (now != NULL && now->nowchamp != NULL)
    {
        if (now->nowchamp->number == nbr)
            now->nowchamp->alive = field->cycle;
        now = now->next;
    }
}

void live(t_field *field, t_process *process)
{
    int nbrplayer;

    nbrplayer = map_to_int(field, process->pos + 1, 4);
    if (nbrplayer < 0)
        nbrplayer = nbrplayer * -1;
    isindex(field, nbrplayer);
    process->lastcyclelive = field->cycle;
}

void zjmp(t_field *field, t_process *process)
{
    if(process->carry == 1)
        process->pos = (process->pos + (map_to_int(field, process->pos+1,2)%IDX_MOD))%MEM_SIZE;
}

int gettype(int argumentcode, int number, t_process *process)
{
    int type;

    type = argumentcode >> (6 - (number * 2)) & table[process->cop].typeparams[number];
    return (type); 
}

int res(int *bytesize, int type, t_field * field, t_process *process)
{
    int result;

    result = 0;
    if (type == REG_CODE)
    {
        result = (process->reg[map_to_int(field, process->pos + *bytesize, 1)]);
        *bytesize += 1;
    }
    else if (type == DIR_CODE)
    {
        result = map_to_int(field, process->pos + *bytesize, table[process->cop].dir_size);
        *bytesize += table[process->cop].dir_size;
    }
    else if (type == IND_CODE)
    {
        result = map_to_int(field, process->pos + map_to_int(field, process->pos + *bytesize, IND_SIZE), 4);
        *bytesize += IND_SIZE;
    }
    return (result);
}


void and(t_field *field, t_process *process)
{
    int argumentcode;
    int param[table[process->cop].countofparams];
    int type;
    int i;
    int bytesize;

    i = 0;
    bytesize = 2;
    param[0] = 0;
    param[1] = 0;
    argumentcode = map_to_int(field, process->pos + 1, 1);
    while (i < table[process->cop].countofparams - 1)
    {
        type = gettype(argumentcode, i, process);
        param[i] = res(&bytesize, type, field, process);
        i++;
    }
    process->reg[map_to_int(field, process->pos + bytesize, 1)] = param[0] & param[1];
    if(process->reg[map_to_int(field, process->pos + bytesize, 1)] == 0)
        process->carry =1;
}