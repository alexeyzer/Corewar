/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procgo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:29:44 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/27 20:40:35 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		is_op(t_field *field, t_process *process)
{
	int i;
	int code;

	code = map_to_int(field, process->pos, 1);
	i = 0;
	while (i < 16)
	{
		if (g_table[i].code == code)
			return (i);
		i++;
	}
	return (MISTAKESYMB);
}

void	workwithproc(t_field *field)
{
	t_process *now;

	now = becomelast(field->first);
	while (now != NULL)
	{
		if (now->moved == 1 && now->idle == 0)
		{
			now->cop = is_op(field, now);
			now->idle = getcyclesforcop(now);
			now->moved = 0;
		}
		if (now->moved == 0 && now->idle > 0)
			now->idle--;
		if (now->moved == 0 && now->idle == 0)
		{
			executer(field, now);
			if (now->cop != 8 || (now->cop == 8 && now->carry == 0))
				now->pos = (now->pos + now->bytetonextсop) % MEM_SIZE;
			now->bytetonextсop = 0;
			now->moved = 1;
			now->cop = -1;
		}
		now = now->prev;
	}
}

int		countoflivepc(t_field *field)
{
	t_process	*head;
	int			count;

	count = 0;
	head = field->first;
	while (head != NULL)
	{
		count++;
		head = head->next;
	}
	return (count);
}

void	play(t_field *field)
{
	while (countoflivepc(field)  > 1)
	{
		field->cycle++;
		workwithproc(field);
		check(field);
		if (field->cycle == field->dump)
			field_print(field);
	}
}
