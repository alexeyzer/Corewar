/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:24:43 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/26 20:59:18 by aguiller         ###   ########.fr       */
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
		if ((result = ((argtype >> (6 - (i * 2)))
			& g_table[process->cop].typeparams[i])) == 0)
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

	bytes = 0;
	while (i++ < g_table[process->cop].countofparams)
	{
		argtype = ((map_to_int(field, process->pos + 1, 1)\
			>> (5 - (i * 2))) & g_table[process->cop].typeparams[i]);
		if (argtype == REG_CODE)
		{
			reg = map_to_int(field, process->pos + 2 + bytes, 1);
			if (reg >= REG_NUMBER)
				return (MISTAKESYMB);
			else
				bytes += 1;
		}
		else if (argtype == IND_CODE)
			bytes += IND_SIZE;
		else if (argtype == DIR_CODE)
			bytes += g_table[process->cop].dir_size;
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
		temporary = (argtype >> (6 - (i * 2)))\
			& (REG_CODE | DIR_CODE | IND_CODE);
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
			else if (result == 2 && isregcorret(field, process, -1))
				mainexecuter(field, process);
			if (process->cop > 16)
				ft_printf("aaa");
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

int		calcpos(int pos, int size)
{
	int newpos;

	newpos = pos + size - 1;
	if (newpos < 0)
		return (MEM_SIZE + newpos);
	else
		return (newpos % MEM_SIZE);
}
