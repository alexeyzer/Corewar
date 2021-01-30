/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:02:22 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/29 22:49:13 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	multiplyfunc(t_field *field, t_process *process)
{
	signed char	argumentcode;
	int			param[g_table[process->cop].countofparams];
	int			type;
	int			i;
	int			bytesize;

	i = 0;
	bytesize = 2;
	argumentcode = onebyte(field, process->pos + 1);
	while (i < g_table[process->cop].countofparams - 1)
	{
		type = gettype(argumentcode, i);
		param[i] = res(&bytesize, type, field, process);
		i++;
	}
	helpfunc(map_to_int(field, process->pos + bytesize, 1), \
		param[0], param[1], process);
}

void	st(t_field *field, t_process *process)
{
	signed char	argumentcode;
	int			reg1;
	int			type;
	int			i;
	int			bytesize;

	i = 0;
	bytesize = 2;
	argumentcode = onebyte(field, process->pos + 1);
	reg1 = map_to_int(field, process->pos + bytesize, 1);
	bytesize += 1;
	type = gettype(argumentcode, 1);
	if (type == REG_CODE)
		process->reg[((map_to_int(field, process->pos + bytesize, 1) \
			- 1))] = process->reg[(reg1 - 1)];
	else if (type == IND_CODE)
	{
		i = map_to_int(field, process->pos + bytesize, IND_SIZE) % IDX_MOD;
		int_to_map(field, process->pos + i, REG_SIZE, \
			process->reg[reg1 - 1]);
		color_to_map(field, process->pos + i, REG_SIZE, process->color);
	}
}

void	my_fork(t_field *field, t_process *process)
{
	int	addr;

	addr = map_to_int(field, process->pos + 1, DIR_CODE);
	if (process->cop == 11)
		addr = addr % IDX_MOD;
	for_fork(field, process, addr);
}

void	aff(t_field *field, t_process *process)
{
	int i;

	i = map_to_int(field, process->pos + 1, 1);
	if (field->aff == 1)
		ft_printf("aff: %d\n", (char)(process->reg[(i - 1)]));
}
