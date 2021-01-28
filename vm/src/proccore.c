/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:20:42 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/28 17:18:20 by aguiller         ###   ########.fr       */
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
	if (res->pos < 0)
		res->pos = MEM_SIZE + res->pos;
	res->parent = parent->parent;
	head = becomelast(field->first);
	head->next = res;
	res->prev = head;
	res->next = NULL;
}

t_process	*createproc(t_champlist *parent, int num)
{
	t_process	*res;
	int			i;

	i = 1;
	res = (t_process*)malloc(sizeof(t_process));
	res->carry = 0;
	res->pos = (MEM_SIZE / num) * (parent->nowchamp->number - 1);
	res->color = parent->nowchamp->color;
	res->idle = 0;
	res->lastcyclelive = -1;
	res->moved = 1;
	res->cop = -1;
	res->bytetonextсop = 0;
	res->next = NULL;
	res->prev = NULL;
	res->parent = parent;
	res->reg = (int*)malloc(sizeof(int) * REG_NUMBER);
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

t_process	*becomelast(t_process *head)
{
	while (head->next != NULL)
		head = head->next;
	return (head);
}

t_process	*init_proc(t_field *field)
{
	t_process	*newprocess;
	t_champlist	*now;
	int			num;

	num = getcountoflist(field->champlist);
	now = field->champlist;
	newprocess = createproc(now, num);
	field->first = newprocess;
	now = now->next;
	while (now != NULL && now->nowchamp != NULL)
	{
		newprocess = addproc(now, num, newprocess);
		now = now->next;
	}
	return (newprocess);
}
