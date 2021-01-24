/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_p1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:23:33 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/24 16:41:01 by aguiller         ###   ########.fr       */
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