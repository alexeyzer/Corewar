/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procgo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:29:44 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/20 18:38:22 by aguiller         ###   ########.fr       */
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

int is_live(t_process *proc)
{
    return (0);
}

void node_op(t_field *field, t_process *proc)
{
    int number;

    if ((number = is_op(field->mass[proc->pos].cell)) != MISTAKESYMB)
    {
        
    }
}

void play(t_field *field)
{

}