/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:36:56 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/26 14:21:52 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				is_key_a(char *curr, t_field *field)
{
	if (!curr)
		return (MISTAKESYMB);
	if (ft_strequ(curr, "-a"))
	{
		field->aff = 1;
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

t_field			*init(void)
{
	t_field	*field;
	int		i;

	i = 0;
	field = (t_field*)malloc(sizeof(t_field));
	field->champlist = (t_champlist*)malloc(sizeof(t_champlist));
	field->champlist->next = NULL;
	field->champlist->prev = NULL;
	field->champlist->nowchamp = NULL;
	field->now = field->champlist;
	field->first = NULL;
	field->cycle = 0;
	field->aff = 0;
	field->countlive = 0;
	field->checks = 0;
	field->cycles_to_die = CYCLE_TO_DIE;
	field->current = field->first;
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

	newlist = (t_champlist*)malloc(sizeof(t_champlist));
	newlist->next = NULL;
	newlist->prev = now;
	newlist->nowchamp = NULL;
	now->next = newlist;
	now = now->next;
	return (now);
}
