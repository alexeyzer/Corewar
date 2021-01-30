/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:13:21 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/30 17:44:13 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		start_pal(int i)
{
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	if (i >= 2)
	{
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_BLUE, COLOR_BLACK);
	}
	if (i >= 3)
		init_pair(3, COLOR_GREEN, COLOR_BLACK);
	if (i == 4)
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
}

int			is_process(t_field *field, int pos)
{
	t_process *head;

	head = field->first;
	while (head->next != NULL)
	{
		if (head->pos == pos)
			return (head->parent->nowchamp->number);
		head = head->next;
	}
	return (0);
}

static void	print_stat(t_field *field)
{
	t_champlist *head;

	wprintw(stdscr, "Turn %d Colors: 1 - RED, 2 - BLUE,\
		3 - GREEN, 4 - YELLOW \n", field->cycle);
	head = field->champlist;
	while (head->next != NULL)
	{
		wprintw(stdscr, "Player name: %s, player live %d\
			live processes - %d \n", head->nowchamp->inf->prog_name,
			head->nowchamp->alive, search_parent(head, field));
		head = head->next;
	}
}

void		field_print_cur(t_field *field)
{
	int i;

	i = 0;
	start_pal(getcountoflist(field->champlist));
	print_stat(field);
	while (i < MEM_SIZE)
	{
		attrset(COLOR_PAIR(set_color(field->mass[i].color)));
		if (is_process(field, i) != 0)
			attrset(A_UNDERLINE);
		wprintw(stdscr, " %02x", field->mass[i].cell);
		i++;
		attroff(A_COLOR);
		attroff(A_UNDERLINE);
	}
	wrefresh(stdscr);
	usleep(75);
	erase();
}
