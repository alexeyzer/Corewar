/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainexecuter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:31:11 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/30 01:29:13 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	sti(t_field *field, t_process *process)
{
	signed char	argumentcode;
	int			param[g_table[process->cop].countofparams];
	int			type;
	int			i;
	int			bytesize;

	bytesize = 2;
	i = 0;
	argumentcode = onebyte(field, process->pos + 1);
	while (i < g_table[process->cop].countofparams)
	{
		type = gettype(argumentcode, i);
		param[i] = res(&bytesize, type, field, process);
		i++;
	}
	bytesize = (param[1] + param[2]) % IDX_MOD;
	int_to_map(field, process->pos + bytesize,\
		DIR_SIZE, param[0]);
	color_to_map(field, process->pos + bytesize, DIR_SIZE, process->color);
}

void	mainexecuter(t_field *field, t_process *process)
{
	g_table[process->cop].exec(field, process);
}

void	int_to_map(t_field *field, int pos, int size, int data)
{
	int	i;

	i = 0;
	while (size)
	{
		field->mass[calcpos(pos + size - 1)].cell =\
			(unsigned char)((data >> i) & 0xFF);
		size--;
		i += 8;
	}
}

void	color_to_map(t_field *field, int pos, int size, char color)
{
	while (size)
	{
		field->mass[calcpos(pos + size - 1)].color = color;
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
