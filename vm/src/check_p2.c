/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgonzo <cgonzo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:30:56 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/28 16:18:58 by cgonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	deleter(t_process *head)
{
	while (head->next != NULL)
	{
		deleter(head->next);
		head->next = NULL;
	}
	free(head->reg);
	free(head);
}

void	deleteallproc(t_field *field)
{
	if (field->first != NULL)
	{
		deleter(field->first);
		field->first = NULL;
	}
}

int		getcyclesforcop(t_process *now)
{
	if (now->cop == -1)
		return (0);
	else
		return (g_table[now->cop].cycle);
}

int		istypecorrectnoargreg(t_field *field, t_process *process)
{
	int	i;
	int	size;
	int reg;

	i = 0;
	size = 1;
	while (i < g_table[process->cop].countofparams)
	{
		if (g_table[process->cop].typeparams[i] == T_REG)
		{
			reg = map_to_int(field, process->pos + size, 1);
			if (reg > REG_NUMBER || reg <= 0)
				return (MISTAKESYMB);
			size += 1;
		}
		else
		{
			if (g_table[process->cop].typeparams[i] == T_DIR)
				size += g_table[process->cop].dir_size;
			if (g_table[process->cop].typeparams[i] == T_IND)
				size += IND_SIZE;
		}
		i++;
	}
	return (1);
}

int		skipnoarg(t_process *process)
{
	int	result;
	int	i;

	result = 1;
	i = 0;
	while (i < g_table[process->cop].countofparams)
	{
		if (g_table[process->cop].typeparams[i] == T_REG)
			result += 1;
		else if (g_table[process->cop].typeparams[i] == T_DIR)
			result += g_table[process->cop].dir_size;
		else if (g_table[process->cop].typeparams[i] == T_IND)
			result += IND_SIZE;
		i++;
	}
	return (result);
}
