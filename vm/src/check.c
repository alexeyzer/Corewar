/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:50:11 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/29 09:45:53 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		checklivenbr(t_field *field)
{
	if (field->countlive >= NBR_LIVE)
	{
		field->cycles_to_die -= CYCLE_DELTA;
		field->checks = 0;
		field->countlive = 0;
	}
	else
		field->checks++;
	if (field->checks >= MAX_CHECKS)
	{
		field->cycles_to_die -= CYCLE_DELTA;
		field->checks = 0;
		field->countlive = 0;
	}
}

t_process	*delete2(t_process *current)
{
	t_process	*ret;

	ret = current->next;
	if (ret != NULL)
	{
		current->prev->next = ret;
		ret->prev = current->prev;
		current->next = NULL;
		current->prev = NULL;
	}
	else
	{
		current->prev->next = NULL;
		current->prev = NULL;
		current->next = NULL;
	}
	free(current);
	return (ret);
}

t_process	*delete(t_field *field, t_process *current)
{
	t_process *head;
	t_process *next;

	head = field->first;
	if (head == current)
	{
		next = (head->next);
		if (next != NULL)
			next->prev = NULL;
		field->first = next;
		free(current);
		return (field->first);
	}
	else
		return (delete2(current));
}

void		findanddeletedied(t_field *field)
{
	t_process	*now;

	now = field->first;
	while (now != NULL)
	{
		if (now->lastcyclelive <= (field->cycle - field->cycles_to_die)\
			|| field->cycles_to_die <= 0)
			now = delete(field, now);
		else
			now = now->next;
	}
}

void		check(t_field *field)
{
	if (field->cyclecheck == field->cycles_to_die || field->cycles_to_die <= 0)
	{
		findanddeletedied(field);
		checklivenbr(field);
		field->cyclecheck = 0;
	}
}
