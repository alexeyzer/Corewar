/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:11:19 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/11 12:40:29 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int getsizeoft(int type, int numcommand)
{
	if (type == T_REG)
		return (1);
	else if (type == T_IND)
		return (2);
	else if (type == T_DIR)
		return (table[numcommand].dir_size);
	return (0);
}

void	summsize(t_corewar *corewar)
{
	t_asm *now;
	int		size;

	size = 0;
	now = corewar->head;
	while (now != NULL)
	{
		size += now->size;
		now = now->next;
	}
	corewar->initial->prog_size = size;
}

void	getsizeall(t_corewar *corewar)
{
	t_asm *now;
	int		size;
	int		i;

	now = corewar->head;
	while (now != NULL)
	{
		if (now->command != NULL)
		{
			i = 0;
			size = 1 + table[now->command->commandnum].argumentcode;
			while(i < table[now->command->commandnum].countofparams)
			{
				size += getsizeoft(now->command->typeparams[i], now->command->commandnum);
				i++;
			}
			now->size = size;
			now = now->next;
		}
		else
			now = now->next;
	}
	summsize(corewar);
}
