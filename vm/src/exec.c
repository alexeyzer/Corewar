/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:24:43 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/21 21:14:15 by alexzudin        ###   ########.fr       */
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
	argtype = bytecode_to_int(&(field->mass[process->pos + 1].cell), 1);
	while (i < table[process->cop].countofparams)
	{
		if ((result = ((argtype >> (6 - (i * 2)))& table[process->cop].typeparams[i])) == 0)
			return (MISTAKESYMB);
		if (result == T_REG)
			reg++;
		i++;
	}
	if (reg != 0 )
		return (2);
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
	result = 0;
	temporary = 0;
	argtype = bytecode_to_int(&(field->mass[process->pos + 1].cell), 1);
	while (i < table[process->cop].countofparams)
	{
		temporary = (argtype  >> (6 - (i * 2))) & (T_REG | T_DIR | T_IND);
		if (temporary == T_REG)
			result += REG_SIZE;
		else if (temporary == T_IND)
			result += IND_SIZE;
		else if (temporary == T_DIR)
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
			{
			
			}
			else if (result == 2)//присуттвует регистр надо сначала проверить корректен ли номер регистра если да выполнить команду; если нет пропустить
			{
			
			}
			else//некоректный код типов аргумент специалный пропуск
				process->bytetonextсop = 1 + 1 + skip(field, process);
		}
		else//если кода типа аргумента нет
		{
			
		}
	}
	else// команда не валидна переместиться на один байт вперед
		process->bytetonextсop = 1;
}