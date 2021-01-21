/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procgo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:29:44 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/21 20:55:52 by alexzudin        ###   ########.fr       */
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


void workwithproc(t_field *field)
{
    t_process *now;

    now = field->first;
    while (now != NULL)
    {
        if (now->moved == 1 && now->bytetonextсop == 0)
        {
            now->cop = is_op(field->mass[now->pos].cell);
            now->idle =  getcyclesforcop(now);
            now->moved = 0;
        }
        if (now->moved == 0 && now->idle > 0)
            now->idle--;
        if (now->moved == 0 && now->idle == 0)
        {
            executer(field, now); //выполняет операцию если она валидна; проверяет код аргументов на валидность; если присутстувует 
            //move(); перемещает на сколько то байт и ставит now->moved = 1
        }
        now = now->next;
    }
}

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
        workwithproc(field);
        check(field);//проверяет каждый cycle_to_die коретки
    }

}