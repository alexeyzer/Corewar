/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obliterator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:48:00 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/26 14:28:24 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	destroy_champ_list(t_champlist *list)
{
	while (list != NULL && list->next != NULL)
	{
		destroy_champ_list(list->next);
		list->next = NULL;
		list->prev = NULL;
	}
	if (list != NULL)
	{
		if (list->nowchamp != NULL)
		{
			if (list->nowchamp->inf != NULL)
				free(list->nowchamp->inf);
			if (list->nowchamp->execcode != NULL)
				free(list->nowchamp->execcode);
			free(list->nowchamp);
		}
		free(list);
	}
}

void	destroy_field(t_field **field)
{
	if (*field != NULL)
	{
		deleteallproc(*field);
		(*field)->current = NULL;
		(*field)->first = NULL;
		destroy_champ_list((*field)->champlist);
		(*field)->champlist = NULL;
		free(*field);
	}
}

int		exiter(t_field *field, char *strtoprint)
{
	ft_printf("%s\n", strtoprint);
	destroy_field(&field);
	exit(0);
	return (1);
}
