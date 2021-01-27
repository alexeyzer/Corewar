/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainexecuter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:31:11 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/27 12:56:04 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	sti(t_field *field, t_process *process)
{
	int	argumentcode;
	int	param[g_table[process->cop].countofparams];
	int	type;
	int	i;
	int	bytesize;

	bytesize = 2;
	i = 0;
	argumentcode = map_to_int(field, process->pos + 1, 1);
	while (i < g_table[process->cop].countofparams)
	{
		type = gettype(argumentcode, i);
		param[i] = res(&bytesize, type, field, process);
		i++;
	}
	int_to_map(field, process->pos + ((param[1] + param[2]) % IDX_MOD),\
		4, param[0]);
}

void	mainexecuter(t_field *field, t_process *process)
{
	if (process->cop == 0)
		live(field, process);
	else if (process->cop == 8)
		zjmp(field, process);
	else if (process->cop == 5 || process->cop == 6 || process->cop == 7)
		multiplyfunc(field, process);
	else if (process->cop == 2)
		st(field, process);
	//else if (process->cop == 11 || process->cop == 14)
	//	my_fork(field, process);
	else if (process->cop == 15)
		aff(field, process);
	else if (process->cop == 3 || process->cop == 4)
		arith(field, process);
	else if (process->cop == 1)
		load(field, process);
	else if (process->cop == 9 || process->cop == 13)
		ldi(field, process);
	else if (process->cop == 12)
		lld(field, process);
	else if (process->cop == 10)
		sti(field, process);
}

void	int_to_map(t_field *field, int pos, int size, int data)
{
	int	i;

	i = 0;
	while (size)
	{
		field->mass[calcpos(pos, size)].cell =\
			(unsigned char)((data >> i) & 0xFF);
		size--;
		i += 8;
	}
}

void	color_to_map(t_field *field, int pos, int size, char color)
{
	while (size)
	{
		field->mass[calcpos(pos, size)].color = color;
		size--;
	}
}

t_champ	*createchamp(void)
{
	t_champ *newchamp;

	newchamp = NULL;
	newchamp = (t_champ*)malloc(sizeof(t_champ));
	newchamp->inf = (t_header*)malloc(sizeof(t_header));
	newchamp->execcode = NULL;
	newchamp->number = 100;
	newchamp->color = 'c';
	newchamp->alive = -1;
	return (newchamp);
}
