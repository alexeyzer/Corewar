/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obliterator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:48:00 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/29 09:35:46 by alexzudin        ###   ########.fr       */
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
		free((*field)->mass);
		deleteallproc(*field);
		(*field)->first = NULL;
		destroy_champ_list((*field)->champlist);
		(*field)->champlist = NULL;
		free(*field);
	}
}

int		exiter(t_field *field, char *strtoprint)
{
	if (strtoprint != NULL)
		ft_printf("%s\n", strtoprint);
	destroy_field(&field);
	exit(0);
	return (1);
}
