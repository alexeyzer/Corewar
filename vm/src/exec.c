/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:24:43 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/28 14:15:13 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		istypecorrect(t_field *field, t_process *process)
{
	int argtype;
	int	i;
	int reg;
	int result;

	i = 0;
	reg = 0;
	argtype = map_to_int(field, process->pos + 1, 1);
	while (i < g_table[process->cop].countofparams)
	{
		result = gettype(argtype, i);
		if (checkmystake(process, result, i) == -1)
			return (MISTAKESYMB);
		if (result == REG_CODE)
			reg++;
		i++;
	}
	if (reg != 0)
		return (2);
	return (1);
}

int		isregcorret(t_field *field, t_process *process, int i)
{
	int reg;
	int	bytes;
	int argtype;
	int type;

	argtype = map_to_int(field, process->pos + 1, 1);
	bytes = 0;
	while (i < g_table[process->cop].countofparams)
	{
		type = gettype(argtype, i);
		if (type == REG_CODE)
		{
			reg = map_to_int(field, process->pos + 2 + bytes, 1);
			if (reg > REG_NUMBER || reg <= 0)
				return (MISTAKESYMB);
			else
				bytes += 1;
		}
		else if (type == IND_CODE)
			bytes += IND_SIZE;
		else if (type == DIR_CODE)
			bytes += g_table[process->cop].dir_size;
		i++;
	}
	return (1);
}

int		skip(t_field *field, t_process *process)
{
	int	argtype;
	int	i;
	int	result;
	int	temporary;

	argtype = 0;
	i = 0;
	result = 2;
	temporary = 0;
	argtype = map_to_int(field, process->pos + 1, 1);
	while (i < g_table[process->cop].countofparams)
	{
		temporary = gettype(argtype, i);
		if (temporary == REG_CODE)
			result += 1;
		else if (temporary == IND_CODE)
			result += IND_SIZE;
		else if (temporary == DIR_CODE)
			result += g_table[process->cop].dir_size;
		i++;
	}
	return (result);
}

void	executer(t_field *field, t_process *process)
{
	int	result;

	result = 0;
	if (process->cop != -1)
	{
		if (g_table[process->cop].argumentcode == 1)
		{
			if ((result = istypecorrect(field, process)) == 1)
				mainexecuter(field, process);
			else if (result == 2 && isregcorret(field, process, 0) != -1)
				mainexecuter(field, process);
			process->bytetonextсop = skip(field, process);
		}
		else
		{
			if (istypecorrectnoargreg(field, process) == 1)
				mainexecuter(field, process);
			process->bytetonextсop = skipnoarg(process);
		}
	}
	else
		process->bytetonextсop = 1;
}

int		calcpos(int pos)
{
	if (pos < 0)
		pos = pos * -1;
	return (pos % MEM_SIZE);
}
