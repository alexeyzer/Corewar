/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:20:42 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/30 00:27:21 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		for_fork(t_field *field, t_process *parent, int adr)
{
	t_process	*res;
	t_process	*head;
	int			i;

	res = NULL;
	res = createproc(parent->parent, parent->parent->nowchamp->number);
	i = 0;
	res->color = parent->color;
	res->lastcyclelive = parent->lastcyclelive;
	res->carry = parent->carry;
	while (i < REG_NUMBER)
	{
		res->reg[i] = parent->reg[i];
		i++;
	}
	res->pos = calcpos(parent->pos + adr);
	res->parent = parent->parent;
	head = field->first;
	head->prev = res;
	res->next = head;
	field->first = res;
}

t_process	*createproc(t_champlist *parent, int num)
{
	t_process	*res;
	int			i;

	i = 1;
	res = (t_process*)malloc(sizeof(t_process));
	res->carry = 0;
	res->pos = (MEM_SIZE / num) * ((parent->nowchamp->number * -1) - 1);
	res->color = parent->nowchamp->color;
	res->idle = 0;
	res->lastcyclelive = -1;
	res->moved = 1;
	res->cop = -1;
	res->bytetonextсop = 0;
	res->next = NULL;
	res->prev = NULL;
	res->parent = parent;
	res->reg[0] = parent->nowchamp->number;
	while (i < REG_NUMBER)
	{
		res->reg[i] = 0;
		i++;
	}
	return (res);
}

t_process	*addproc(t_champlist *parent, int num, t_process *head)
{
	t_process *proc;

	proc = createproc(parent, num);
	head->next = proc;
	proc->prev = head;
	return (proc);
}

t_process	*init_proc(t_field *field)
{
	t_process *current;

	if (field->now->nowchamp == NULL)
		field->now = field->now->prev;
	field->first = createproc(field->now, getcountoflist(field->champlist));
	current = field->first;
	field->now = field->now->prev;
	while (field->now != NULL)
	{
		if (field->now->nowchamp != NULL)
			current = addproc(field->now,\
				getcountoflist(field->champlist), current);
		field->now = field->now->prev;
	}
	return (field->first);
}
