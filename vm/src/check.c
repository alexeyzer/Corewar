/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:50:11 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/22 11:36:24 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void checklivenbr(t_field *field)
{
	if (field->countlive >= NBR_LIVE)
	{
		field->cycles_to_die -= CYCLE_DELTA;
		field->checks = 0;
	}
	else
		field->checks++;
	if (field->checks >= MAX_CHECKS)
	{
		field->cycles_to_die -= CYCLE_DELTA;
		field->checks = 0;
	}
	field->countlive = 0;
}

t_process *delete2(t_field *field, t_process *current)
{
	t_process *head;
	t_process *ret;

	head = field->first;
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

t_process *delete(t_field *field, t_process *current)
{
	t_process *head;

	head = field->first;
	if (head == current)
	{
		field->first = field->first->next;
		if (field->first != NULL)
			field->first->prev = NULL;
		current->next = NULL;
		free(current);
		return(field->first);
	}
	else
		return (delete2(field, current));
}

void findanddeletedied(t_field *field)
{
	t_process *now;

	now = field->first;
	while (now != NULL)
	{
		if (now->lastcyclelive < (field->cycle - field->cycles_to_die))
			now = delete(field, now);
		else
			now = now->next;
	}
}

void check(t_field *field)
{
    if (field->cycles_to_die < 0)
        deleteallproc(field);
    else
    {
        if (field->cycle % field->cycles_to_die == 0)
        {
            findanddeletedied(field);//убивает коретки которые выполнили операцию live больше чем cycles_to_die назад
            checklivenbr(field);//уменьшается если countlive >= nbrlive|| live обнуляется|nbr chekcs обнуляется при live >= nbrlive или когда nbrcheck = NBRCHEKSMAX
        }
    }
}