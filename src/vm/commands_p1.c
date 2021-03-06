/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_p1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:23:33 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/31 20:24:36 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	isindex(t_field *field, int nbr)
{
	t_champlist *now;

	now = field->champlist;
	while (now != NULL && now->nowchamp != NULL)
	{
		if (now->nowchamp->number == nbr)
		{
			now->nowchamp->alive = field->cycle;
			if (field->l == 1)
				ft_printf("A process shows that player %d %s is alive\n",\
					now->nowchamp->number * -1,\
						now->nowchamp->inf->prog_name);
		}
		now = now->next;
	}
}

void	live(t_field *field, t_process *process)
{
	int nbrplayer;

	nbrplayer = map_to_int(field, process->pos + 1, 4);
	field->countlive++;
	isindex(field, nbrplayer);
	process->lastcyclelive = field->cycle;
}

void	zjmp(t_field *field, t_process *process)
{
	int pos;

	pos = (map_to_int(field, process->pos + 1, 2)) % IDX_MOD;
	if (process->carry == 1)
		process->pos = process->pos + pos;
}

int		gettype(signed char argumentcode, int number)
{
	signed char	type;
	int			all;

	type = argumentcode;
	all = (REG_CODE | DIR_CODE | IND_CODE);
	if (number == 0)
		type = type & 0xC0;
	if (number == 1)
		type = type & 0x30;
	if (number == 2)
		type = type & 0x0C;
	type = type >> (6 - (number * 2));
	type = type & all;
	return (type);
}

int		res(int *byte, int type, t_field *field, t_process *process)
{
	int result;
	int reg;

	result = 0;
	if (type == REG_CODE)
	{
		reg = map_to_int(field, process->pos + *byte, 1) - 1;
		result = (process->reg[(reg)]);
		*byte += 1;
	}
	else if (type == DIR_CODE)
	{
		result = map_to_int(field, process->pos
			+ *byte, g_table[process->cop].dir_size);
		*byte += g_table[process->cop].dir_size;
	}
	else if (type == IND_CODE)
	{
		result = map_to_int(field, process->pos +
			(map_to_int(field, process->pos + *byte, IND_SIZE))\
				% IDX_MOD, DIR_SIZE);
		*byte += IND_SIZE;
	}
	return (result);
}
