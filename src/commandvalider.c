/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandvalider.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 08:32:22 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/05 15:57:30 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void initasm(t_corewar *corewar)
{
	corewar->head = (t_asm*)malloc(sizeof(t_asm));
	corewar->head->command = NULL;
	corewar->head->size = 0;
	corewar->head->next = NULL;
	corewar->head->prev = NULL;
	corewar->head->label = NULL;
}

int commandparser(t_corewar *corewar)
{
	char *line;

	initasm(corewar);
    while	(get_str(corewar->fd, &line) > 0)//ожидаю либо comment либо label libo command with params
	{
		if (*line == '\0')
            continue ;
        else if (isitcomment(line) == 0)
        {
			
        }
		if (line != NULL)
			ft_strdel(&line);
		(corewar->currentline)++;
	}
    return (1);
	
}