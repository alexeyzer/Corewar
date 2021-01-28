/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamesult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgonzo <cgonzo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 13:38:17 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/28 14:38:37 by cgonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		printplayers(t_field *field)
{
	int			i;
	t_champlist	*now;

	now = field->champlist;
	i = 1;
	ft_printf("Introducing contestants...\n");
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
	int			count;

	now = field->champlist;
	count = issamelustlive(field, max);
	while (now != NULL && now->nowchamp != NULL)
	{
		if (now->nowchamp->alive == max && count == 1)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n",\
			now->nowchamp->number, now->nowchamp->inf->prog_name);
			return ;
		}
		if (now->nowchamp->alive == max && count > 1 && now->nowchamp->number\
			== field->lastprocesssadlust)
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
	if (max == -1)
	{
		now = brcomelust(field->champlist);
		ft_printf("Contestant %d, \"%s\", has won !\n",\
			now->nowchamp->number, now->nowchamp->inf->prog_name);
	}
	else if (max != -1)
		winner(field, max);
}

int			map_to_int(t_field *field, int pos, int size)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = (field->mass[calcpos(pos)].cell & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((field->mass[calcpos(pos + size - 1)].cell ^ 0xFF)\
				<< (i * 8));
		else
			result += (field->mass[calcpos(pos + size - 1)].cell << (i * 8));
		size--;
		i++;
	}
	if (sign)
		result = ~(result);
	return (result);
}
