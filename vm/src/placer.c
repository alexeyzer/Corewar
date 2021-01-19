/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgonzo <cgonzo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:19:30 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/19 17:40:30 by cgonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int getcountoflist(t_champlist *head)
{
    int i;

    i = 0;
    while (head != NULL && head->nowchamp != NULL)
    {
        i++;
        head = head->next;
    }
    return (i);
}

void place(t_field *field)
{
    int delta;
    int j;
    t_champlist *now;

    now = field->champlist;
    delta = MEM_SIZE / getcountoflist(now);
    while(now != NULL && now->nowchamp != NULL)
    {
        j = 0;
        while(j < (int)now->nowchamp->inf->prog_size)
        {
            field->mass[now->nowchamp->number * delta + j].cell = now->nowchamp->execcode[j];
            field->mass[now->nowchamp->number * delta + j].color = now->nowchamp->color;
            j++;
        }
        now = now->next;
    }
}

void printcurrentcolor(t_cell *cell)
{
    if (cell->color == 'a')
        ft_printf(GREEN"%02x "NO, cell->cell);
    if (cell->color == 'b')
        ft_printf(RED"%02x "NO, cell->cell);
    if (cell->color == 'c')
        ft_printf(BLUE"%02x "NO, cell->cell);
    if (cell->color == 'd')
        ft_printf(PINK"%02x "NO, cell->cell);
    if (cell->color == 'z')
        ft_printf("%02x ", cell->cell);

}

void field_print(t_field *field)
{
    int i;

    i = 0;
    while (i < MEM_SIZE)
    {
        if(i % 32 == 0 && i != 0)
            ft_printf("\n");
        printcurrentcolor(&(field->mass[i]));
        i++;
    }
}

void makecolor(t_champlist *head)
{
    while (head != NULL && head->nowchamp != NULL)
    {
        head->nowchamp->color = 'a' + head->nowchamp->number;
        head = head->next;
    }
}