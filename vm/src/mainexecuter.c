/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainexecuter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:31:11 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/25 17:16:14 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void sti(t_field *field, t_process *process)
{
    int argumentcode;
    int param[table[process->cop].countofparams];
    int type;
    int i;
    int bytesize;

    bytesize = 2;
    i = 0;
    argumentcode = map_to_int(field, process->pos + 1, 1);
    while (i < table[process->cop].countofparams - 1)
    {
        type = gettype(argumentcode, i);
        param[i] = res(&bytesize, type, field, process);
        i++;
    }
    int_to_map(field, process->pos + ((param[1] + param[2] )% IDX_MOD)\
		, 4, process->reg[param[0] - 1]);
    process->carry = (process->reg[param[0] - 1] == 0)? 1 : 0;
}

void mainexecuter(t_field *field, t_process *process)
{
    if (process->cop == 0)
        live(field, process);
    else if(process->cop == 8)
        zjmp(field, process);
    else if(process->cop == 5 || process->cop == 6 || process->cop == 7)
        multiplyfunc(field, process);
    else if (process->cop == 2)
        st(field, process);
    else if(process->cop == 14)
        my_fork(field, process);
    else if(process->cop == 11)
        my_fork(field, process);
    else if(process->cop == 15)
        aff(field, process);
    else if(process->cop == 3 || process->cop == 4)
        arith(field, process);
    else if (process->cop == 1)
        load(field, process);
    else if (process->cop == 10 || process->cop == 14)
        ldi(field, process);
    else if (process->cop == 12)
        lld(field, process);
}

void	int_to_map(t_field *field, int pos, int size, int data)
{
	int		i;

	i = 0;
	while (size)
	{
        field->mass[(pos + size - 1) % MEM_SIZE].cell =\
			(unsigned char)((data >> i) & 0xFF);
		size--;
        i +=8;
	}
}

void	color_to_map(t_field *field, int pos, int size, char color)
{
	while (size)
	{
        field->mass[pos + size - 1].color = color;
		size--;
	}
}