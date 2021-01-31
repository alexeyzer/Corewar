/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:36:56 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/31 20:25:13 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				is_key_aorv(char *curr, t_field *field)
{
	if (!curr)
		return (MISTAKESYMB);
	if (ft_strequ(curr, "-a"))
	{
		field->aff = 1;
		return (1);
	}
	if (ft_strequ(curr, "-v"))
	{
		field->v = 1;
		return (1);
	}
	if (ft_strequ(curr, "-l"))
	{
		field->l = 1;
		return (1);
	}
	return (MISTAKESYMB);
}

t_champlist		*isitbusy(t_champlist *head, int number)
{
	while (head != NULL)
	{
		if (head->nowchamp->number == number)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_field			*init(int i, t_field *field)
{
	field = (t_field*)malloc(sizeof(t_field) * 1);
	field->champlist = (t_champlist*)malloc(sizeof(t_champlist) * 1);
	field->champlist->next = NULL;
	field->champlist->prev = NULL;
	field->champlist->nowchamp = NULL;
	field->now = field->champlist;
	field->first = NULL;
	field->isdump = 0;
	field->cycle = 0;
	field->aff = 0;
	field->v = 0;
	field->l = 0;
	field->cyclecheck = 0;
	field->dump = -1;
	field->countlive = 0;
	field->checks = 0;
	field->cycles_to_die = CYCLE_TO_DIE;
	field->mass = (t_cell*)malloc(sizeof(t_cell*) * MEM_SIZE);
	while (i < MEM_SIZE)
	{
		field->mass[i].color = 'z';
		field->mass[i].cell = 0x00;
		i++;
	}
	return (field);
}

t_champlist		*addchamtolist(t_champlist *now)
{
	t_champlist *newlist;

	newlist = (t_champlist*)malloc(sizeof(t_champlist) * 1);
	newlist->next = NULL;
	newlist->prev = now;
	newlist->nowchamp = NULL;
	now->next = newlist;
	now = now->next;
	return (now);
}
