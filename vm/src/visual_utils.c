/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:52:23 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/31 12:42:31 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		set_color(char c)
{
	if (c == 'b')
		return (1);
	else if (c == 'c')
		return (2);
	else if (c == 'd')
		return (3);
	else if (c == 'e')
		return (4);
	return (5);
}

int		search_parent(t_champlist *head, t_field *field)
{
	int			i;
	t_process	*iter;

	i = 0;
	iter = field->first;
	while (iter != NULL)
	{
		if (iter->parent->nowchamp->number == head->nowchamp->number)
			i++;
		iter = iter->next;
	}
	return (i);
}

void	print_usage(void)
{
	ft_printf("Usage: ./corewar [-dump N] [-d N] [-v]\
		 [-a] [[-n number] champion1.cor]\n");
}
