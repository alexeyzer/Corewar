/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_p1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:23:33 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/28 13:53:06 by aguiller         ###   ########.fr       */
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
			now->nowchamp->alive = field->cycle;
		now = now->next;
	}
}

void	live(t_field *field, t_process *process)
{
	int nbrplayer;

	nbrplayer = map_to_int(field, process->pos + 1, 4);
	field->countlive++;
	field->lastprocesssadlust = process->parent->nowchamp->number;
	isindex(field, nbrplayer);
	process->lastcyclelive = field->cycle;
}

void	zjmp(t_field *field, t_process *process)
{
	if (process->carry == 1)
		process->pos = ((process->pos +
			(map_to_int(field, process->pos + 1, 2)) % IDX_MOD)) % MEM_SIZE;
}

int		gettype(int argumentcode, int number)
{
	int type;
	int	all;

	all = (REG_CODE | DIR_CODE | IND_CODE);
	type = argumentcode >> (6 - (number * 2))
		& all;
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
			(map_to_int(field, process->pos + *byte, IND_SIZE)) % IDX_MOD, 4);
		*byte += IND_SIZE;
	}
	return (result);
}
