/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:19:30 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/26 14:26:52 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		getcountoflist(t_champlist *head)
{
	int	i;

	i = 0;
	while (head != NULL && head->nowchamp != NULL)
	{
		i++;
		head = head->next;
	}
	return (i);
}

void	place(t_field *field)
{
	int				delta;
	int				j;
	t_champlist		*now;

	now = field->champlist;
	delta = MEM_SIZE / getcountoflist(now);
	while (now != NULL && now->nowchamp != NULL)
	{
		j = 0;
		while (j < (int)now->nowchamp->inf->prog_size)
		{
			field->mass[(now->nowchamp->number - 1) * delta + j].cell = \
				now->nowchamp->execcode[j];
			field->mass[(now->nowchamp->number - 1) * delta + j].color = \
					now->nowchamp->color;
			j++;
		}
		now = now->next;
	}
}

void	printcurrentcolor(t_cell *cell)
{
	if (cell->color == 'b')
		ft_printf(GREEN"%02x "NO, cell->cell);
	if (cell->color == 'c')
		ft_printf(RED"%02x "NO, cell->cell);
	if (cell->color == 'd')
		ft_printf(BLUE"%02x "NO, cell->cell);
	if (cell->color == 'e')
		ft_printf(PINK"%02x "NO, cell->cell);
	if (cell->color == 'z')
		ft_printf("%02x ", cell->cell);
}

void	field_print(t_field *field)
{
	int i;

	i = 0;
	ft_printf("0x%04x : ", i);
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0 && i != 0)
		{
			ft_printf("\n");
			ft_printf("0x%04x : ", i);
		}
		printcurrentcolor(&(field->mass[i]));
		i++;
	}
	ft_printf("\n");
}

void	makecolor(t_champlist *head)
{
	while (head != NULL && head->nowchamp != NULL)
	{
		head->nowchamp->color = 'a' + head->nowchamp->number;
		head = head->next;
	}
}
