/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:19:30 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/19 12:14:39 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void place(t_field *field)
{
    int delta;
    int j;
    t_champlist *now;

    now = field->champlist;
    delta = MEM_SIZE / field->counter;
    while(now != NULL && now->nowchamp != NULL)
    {
        j = 0;
        while(j < (int)now->nowchamp->inf->prog_size)
        {
            field->mass[now->place * delta + j].cell = now->nowchamp->execcode[j];
            j++;
        }
        now = now->next;
    }
}