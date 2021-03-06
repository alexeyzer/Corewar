/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procgo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:29:44 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/30 17:36:53 by aguiller         ###   ########.fr       */
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

	now = field->first;
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
				now->pos = calcpos(now->pos + now->bytetonextсop);
			now->bytetonextсop = 0;
			now->moved = 1;
			now->cop = -1;
		}
		now = now->next;
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
	if (field->v == 1)
	{
		initscr();
		nodelay(stdscr, FALSE);
		start_color();
	}
	while (countoflivepc(field) > 0)
	{
		field->cycle++;
		field->cyclecheck++;
		workwithproc(field);
		if (field->v == 1)
			field_print_cur(field);
		check(field);
		if (field->cycle == field->dump)
		{
			if (field->v == 1)
				endwin();
			field_print(field);
			exiter(field, NULL);
		}
	}
	if (field->v == 1)
		endwin();
}
