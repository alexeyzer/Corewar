/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:48:56 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/28 14:16:29 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	checkmystake(t_process *p, int result, int i)
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

int	issamelustlive(t_field *field, int max)
{
	t_champlist *now;
	int			count;

	now = field->champlist;
	count = 0;
	while (now != NULL && now->nowchamp != NULL)
	{
		if (now->nowchamp->alive == max)
			count++;
		now = now->next;
	}
	return (count);
}
