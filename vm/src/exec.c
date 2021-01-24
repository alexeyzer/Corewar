/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:24:43 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/24 16:09:57 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int istypecorrect(t_field *field, t_process *process)
{
	int argtype;
	int	i;
	int reg;
	int result;

	argtype = 0;
	i = 0;
	reg = 0;
	argtype = map_to_int(field, process->pos + 1, 1);
	while (i < table[process->cop].countofparams)
	{
		if ((result = ((argtype >> (5 - (i * 2))) & table[process->cop].typeparams[i])) == 0)
			return (MISTAKESYMB);
		if (result == REG_CODE)
			reg++;
		i++;
	}
	if (reg != 0 )
		return (2);
	return (1);
}

int isregcorret(t_field *field, t_process *process)
{
	int i;
	int reg;
	int	bytes;
	int argtype;

	i = 0;
	argtype = 0;
	reg = 0;
	bytes = 0;
	while (i < table[process->cop].countofparams)
	{
		argtype = ((map_to_int(field, process->pos + 1, 1) >> (5 - (i * 2))) & table[process->cop].typeparams[i]);
		if (argtype == REG_CODE)
		{
			reg = map_to_int(field, process->pos + 2 + bytes, 1);
			if (reg >= REG_NUMBER)
				return (MISTAKESYMB);
			else
				bytes += 1;
		}
		else
			if (argtype == IND_CODE)
				bytes += IND_SIZE;
			else if (argtype == DIR_CODE)
				bytes += table[process->cop].dir_size;
		i++;
	}
	return (1);
}

int	skip(t_field *field, t_process *process)
{
	int argtype;
	int	i;
	int result;
	int temporary;

	argtype = 0;
	i = 0;
	result = 2;
	temporary = 0;
	argtype = map_to_int(field, process->pos + 1, 1);
	while (i < table[process->cop].countofparams)
	{
		temporary = (argtype  >> (6 - (i * 2))) & (REG_CODE | DIR_CODE | IND_CODE);
		if (temporary == REG_CODE)
			result += 1;
		else if (temporary == IND_CODE)
			result += IND_SIZE;
		else if (temporary == DIR_CODE)
			result += table[process->cop].dir_size;
		i++;
	}
	return result;	
}

void executer(t_field *field, t_process *process)//в процессе если команда без типов аргументов
{
	int result;

	result = 0;
	if (process->cop != -1)
	{
		if (table[process->cop].argumentcode == 1)
		{
			if ((result = istypecorrect(field, process)) == 1)//валидный без регистра выполнить
				mainexecuter(field, process);
			else if (result == 2 && isregcorret(field, process))//присуттвует регистр надо сначала проверить корректен ли номер регистра если да выполнить команду; если нет пропустить
				mainexecuter(field, process);
			//переходи на байтов вперед
			process->bytetonextсop = skip(field, process);
		}
		else//если кода типов аргумента нет
		{
			if (istypecorrectnoargreg(field, process) == 1)
				mainexecuter(field, process);
			process->bytetonextсop = skipnoarg(process);
		}
	}
	else// команда не валидна переместиться на один байт вперед
		process->bytetonextсop = 1;
}