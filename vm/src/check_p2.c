/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:30:56 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/21 15:33:59 by alexzudin        ###   ########.fr       */
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

void deleteall(t_field *field)
{
	if (field->first != NULL)
	{
		deleter(field->first);
		field->first = NULL;
	}
}