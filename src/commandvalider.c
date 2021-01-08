/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandvalider.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 08:32:22 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/07 22:39:54 by alexzudin        ###   ########.fr       */
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

int isitfromlabel(char a)
{
	int i;

	i = 0;
	while (LABEL_CHARS[i] != '\0')
	{
		if (a == LABEL_CHARS[i])
			return (1);
		i++;
	}
	return (-1);
}

int isitlabel(t_corewar *corewar, char *line)
{
	int i;
	int	j;

	i = 0;
	while((line[i] ==  ' ' || line[i] ==  '\t') && (line[i] != '\n' && line [i] != '\0'))
		i++;
	j = i;
	while (line[i] != LABEL_CHAR && line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && line[i] != '\t')
		i++;
	if (line[i] == LABEL_CHAR)
	{
		i = j;
		while (line[i] != LABEL_CHAR)
		{
			if (isitfromlabel(line[i]) < 0)
			{
				ft_printf("\n|%c|\n with this symbol", line[i]);
				exitcorewar(&corewar, "invalid symbols for Label", corewar->currentline);
			}
			i++;
		}
		return (1);
	}
	else
		return (-1);
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
			if (isitlabel(corewar, line) > 0)
				ft_printf("we have label boys");
        }
		if (line != NULL)
			ft_strdel(&line);
		(corewar->currentline)++;
	}
    return (1);
	
}