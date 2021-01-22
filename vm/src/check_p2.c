/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:30:56 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/22 11:34:48 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void deleter(t_process *head)
{
	while (head->next != NULL)
	{
		deleter(head->next);
		head->next = NULL;
	}
	free(head);
}

void deleteallproc(t_field *field)
{
	if (field->first != NULL)
	{
		deleter(field->first);
		field->first = NULL;
	}
}

int getcyclesforcop(t_process *now)
{
	if (now->cop == -1)
		return (0);
	else
		return(table[now->cop].cycle);
	
}