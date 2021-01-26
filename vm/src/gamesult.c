/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamesult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 13:38:17 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/26 14:10:21 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		printplayers(t_field *field)
{
	int			i;
	t_champlist	*now;

	now = field->champlist;
	i = 1;
	while (now != NULL && now->nowchamp != NULL)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i,\
			now->nowchamp->inf->prog_size, now->nowchamp->inf->prog_name,\
				now->nowchamp->inf->comment);
		i++;
		now = now->next;
	}
}

t_champlist	*brcomelust(t_champlist *list)
{
	while (list->next != NULL && list->next->nowchamp != NULL)
		list = list->next;
	return (list);
}

static void	winner(t_field *field, int max)
{
	t_champlist *now;

	now = field->champlist;
	while (now != NULL && now->nowchamp != NULL)
	{
		if (now->nowchamp->alive == max)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n",\
			now->nowchamp->number, now->nowchamp->inf->prog_name);
			return ;
		}
		now = now->next;
	}
}

void		simpleresult(t_field *field)
{
	int			max;
	t_champlist	*now;

	max = -1;
	now = field->champlist;
	while (now != NULL && now->nowchamp != NULL)
	{
		if (now->nowchamp->alive >= max)
			max = now->nowchamp->alive;
		now = now->next;
	}
	if (max == -1 && field->first == NULL)
	{
		now = brcomelust(field->champlist);
		ft_printf("Contestant %d, \"%s\", has won !\n",\
			now->nowchamp->number, now->nowchamp->inf->prog_name);
	}
	else if (field->first != NULL && max == -1)
		ft_printf("Contestant %d, \"%s\", has won !\n",\
			field->first->parent->nowchamp->number,\
				field->first->parent->nowchamp->inf->prog_name);
	else if (max != -1)
		winner(field, max);
}

int			map_to_int(t_field *field, int pos, int size)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = (field->mass[pos].cell & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((field->mass[(pos + size - 1)\
				% MEM_SIZE].cell ^ 0xFF) << (i * 8));
		else
			result += (field->mass[(pos + size - 1)\
				% MEM_SIZE].cell << (i * 8));
		size--;
		i++;
	}
	if (sign)
		result = ~(result);
	return (result);
}
