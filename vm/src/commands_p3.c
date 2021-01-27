/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_p3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgonzo <cgonzo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:55:23 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/27 15:51:27 by cgonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	helpfunc(int regnbr, int param1, int param2, t_process *process)
{
	if (regnbr > 0)
	{
		if (process->cop == 5)
			process->reg[absreg(regnbr - 1)] = param1 & param2;
		else if (process->cop == 6)
			process->reg[absreg(regnbr - 1)] = param1 | param2;
		else if (process->cop == 7)
			process->reg[absreg(regnbr - 1)] = param1 ^ param2;
		process->carry = (process->reg[regnbr] == 0) ? 1 : 0;
	}
}

void	arith(t_field *field, t_process *process)
{
	int	num;
	int	first;
	int	second;

	num = map_to_int(field, process->pos + 4, 1) - 1;
	first = map_to_int(field, process->pos + 2, 1) - 1;
	second = map_to_int(field, process->pos + 3, 1) - 1;
	if (process->cop == 3)
		process->reg[absreg(num)] = process->reg[absreg(first)] \
			+ process->reg[absreg(second)];
	if (process->cop == 4)
		process->reg[absreg(num)] = process->reg[absreg(first)] \
			- process->reg[absreg(second)];
	process->carry = (process->reg[absreg(num)] == 0) ? 1 : 0;
}

void	load(t_field *field, t_process *process)
{
	int	argumentcode;
	int	param[g_table[process->cop].countofparams];
	int	type;
	int	i;
	int	bytesize;

	i = 0;
	bytesize = 2;
	param[0] = 0;
	param[1] = 0;
	argumentcode = map_to_int(field, process->pos + 1, 1);
	type = gettype(argumentcode, i);
	param[0] = res(&bytesize, type, field, process);
	param[1] = map_to_int(field, process->pos + bytesize, 1);
	process->reg[absreg(param[1] - 1)] = param[0];
	process->carry = (process->reg[absreg(param[1] - 1)] == 0) ? 1 : 0;
}

void	ldi(t_field *field, t_process *p)
{
	int	argumentcode;
	int	param[g_table[p->cop].countofparams];
	int	type;
	int	i;
	int	bytesize;

	i = 0;
	bytesize = 2;
	argumentcode = map_to_int(field, p->pos + 1, 1);
	while (i < g_table[p->cop].countofparams - 1)
	{
		type = gettype(argumentcode, i);
		param[i] = res(&bytesize, type, field, p);
		i++;
	}
	param[2] = map_to_int(field, p->pos + bytesize, 1);
	if (p->cop == 9)
		p->reg[absreg(param[2] - 1)] = map_to_int(field,\
			p->pos + ((param[0] + param[1]) % IDX_MOD), 4);
	else
		p->reg[absreg(param[2] - 1)] = map_to_int(field,\
			p->pos + param[0] + param[1], 4);
	if (p->cop == 13)
		p->carry = (p->reg[absreg(param[2] - 1)] == 0) ? 1 : 0;
}

void	lld(t_field *field, t_process *process)
{
	int	argumentcode;
	int	param[g_table[process->cop].countofparams];
	int	type;
	int	bytesize;

	bytesize = 2;
	argumentcode = map_to_int(field, process->pos + 1, 1);
	type = gettype(argumentcode, 0);
	if (type == DIR_CODE)
	{
		param[0] = map_to_int(field, process->pos +
			bytesize, g_table[process->cop].dir_size);
		bytesize += g_table[process->cop].dir_size;
	}
	else if (type == IND_CODE)
	{
		param[0] = map_to_int(field, process->pos +
			map_to_int(field, process->pos + bytesize, IND_SIZE), 4);
		bytesize += IND_SIZE;
	}
	param[1] = map_to_int(field, process->pos + bytesize, 1);
	process->reg[absreg(param[1] - 1)] = param[0];
	process->carry = (process->reg[absreg(param[1] - 1)] == 0) ? 1 : 0;
}
