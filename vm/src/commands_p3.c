/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_p3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:55:23 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/29 23:09:02 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	helpfunc(int regnbr, int param1, int param2, t_process *process)
{
	if (process->cop == 5)
		process->reg[(regnbr - 1)] = param1 & param2;
	else if (process->cop == 6)
		process->reg[(regnbr - 1)] = param1 | param2;
	else if (process->cop == 7)
		process->reg[(regnbr - 1)] = param1 ^ param2;
	process->carry = (process->reg[regnbr - 1] == 0) ? 1 : 0;
}

void	arith(t_field *field, t_process *process)
{
	int	num;
	int	first;
	int	second;

	first = map_to_int(field, process->pos + 2, 1) - 1;
	second = map_to_int(field, process->pos + 3, 1) - 1;
	num = map_to_int(field, process->pos + 4, 1) - 1;
	if (process->cop == 3)
		process->reg[(num)] = process->reg[(first)] \
			+ process->reg[(second)];
	if (process->cop == 4)
		process->reg[(num)] = process->reg[(first)] \
			- process->reg[(second)];
	process->carry = (process->reg[(num)] == 0) ? 1 : 0;
}

void	load(t_field *field, t_process *process)
{
	signed char	argumentcode;
	int			param[g_table[process->cop].countofparams];
	int			type;
	int			bytesize;

	bytesize = 2;
	param[0] = 0;
	param[1] = 0;
	argumentcode = onebyte(field, process->pos + 1);
	type = gettype(argumentcode, 0);
	param[0] = res(&bytesize, type, field, process);
	param[1] = map_to_int(field, process->pos + bytesize, 1);
	process->reg[(param[1] - 1)] = param[0];
	process->carry = (process->reg[(param[1] - 1)] == 0) ? 1 : 0;
}

void	ldi(t_field *field, t_process *p)
{
	signed char	argumentcode;
	int			par[g_table[p->cop].countofparams];
	int			type;
	int			i;
	int			byte;

	i = 0;
	byte = 2;
	argumentcode = onebyte(field, p->pos + 1);
	while (i < g_table[p->cop].countofparams - 1)
	{
		type = gettype(argumentcode, i);
		par[i] = res(&byte, type, field, p);
		i++;
	}
	par[2] = map_to_int(field, p->pos + byte, 1);
	byte = (p->cop == 9) ? (par[1] + par[0]) % IDX_MOD : (par[1] + par[0]);
	p->reg[(par[2] - 1)] = map_to_int(field, p->pos + byte, 4);
	if (p->cop == 13)
		p->carry = (p->reg[(par[2] - 1)] == 0) ? 1 : 0;
}

void	lld(t_field *field, t_process *process)
{
	signed char	argumentcode;
	int			param[g_table[process->cop].countofparams];
	int			type;
	int			bytesize;

	bytesize = 2;
	argumentcode = onebyte(field, process->pos + 1);
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
	process->reg[(param[1] - 1)] = param[0];
	process->carry = (process->reg[(param[1] - 1)] == 0) ? 1 : 0;
}
