/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:24:43 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/28 09:07:58 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int checkmystake(t_process *p,int result, int i)
{
	if (result == REG_CODE)
	{
		if ((T_REG & g_table[p->cop].typeparams[i]) == 0)
			return (MISTAKESYMB);
		else
			return (1);
		
	}
	else if (result == DIR_CODE)
	{
		if ((T_DIR & g_table[p->cop].typeparams[i]) == 0)
			return (MISTAKESYMB);
		else
			return (1);
		
	}
	else if (result == IND_CODE)
	{
		if ((T_IND & g_table[p->cop].typeparams[i]) == 0)
			return (MISTAKESYMB);
		else
			return (1);
	}
	return (MISTAKESYMB);
}

int		istypecorrect(t_field *field, t_process *process)
{
	int argtype;
	int	i;
	int reg;
	int result;

	i = 0;
	reg = 0;
	argtype = map_to_int(field, process->pos + 1, 1);
	if (process->pos == 2660 && process->lastcyclelive == 3315)
	{
		ft_printf("yeap");
		field_print(field);
	}
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

	i = 0;
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

int		calcpos(int pos, int size)
{
	int newpos;

	newpos = pos + size - 1;
	if (newpos < 0)
		return (MEM_SIZE + newpos);
	else
		return (newpos % MEM_SIZE);
}
