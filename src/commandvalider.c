/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandvalider.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 08:32:22 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/10 12:52:28 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	initasm(t_corewar *corewar)
{
	corewar->head = (t_asm*)malloc(sizeof(t_asm));
	corewar->head->command = NULL;
	corewar->head->size = 0;
	corewar->head->next = NULL;
	corewar->head->prev = NULL;
	corewar->head->label = NULL;
	corewar->now = corewar->head;
}

int		isitfromlabel(char a)
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

int		isitlabel(t_corewar *corewar, char *line)
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
				exitcorewar(&corewar, "invalid symbols for Label", corewar->currentline, line);
			i++;
		}
		return (i);
	}
	else
		return (-1);
}

void	afterlabel(t_corewar *corewar, char *line, int i)
{
	int j;
	int numcommand;

	j = i;
	i++;
	while (line[i] == '\t' || line[i] == ' ')
		i++;
	if (line[i] == '\n')
		addlabel(corewar, line, j);
	else
	{
		if ((numcommand = isitcommand(line, i)) >= 0)
		{
			addlabel(corewar, line, j);
			iscommandcorrect(corewar, line, numcommand, i);
			//if we have command parse + add command + iscommandcorrect?
		}
		else
			exitcorewar(&corewar, "Error with syntax after label", corewar->currentline, line);
	}
}

int		commandparser(t_corewar *corewar)
{
	char	*line;
	int		i;

	initasm(corewar);
    while	(get_str(corewar->fd, &line) > 0)
	{
		if (*line == '\n')
            continue ;
        else if (isitcomment(line) == 0)
        {
			if ( (i = isitlabel(corewar, line)) > 0)
			{
				ft_printf("WE got label:");
				afterlabel(corewar, line, i);
			}
			else if ((i = isitcommand(line, 0)) > 0)
			{
				ft_printf("WE GOT WORK TO DO\n");
				iscommandcorrect(corewar, line, i, 0);
			}
        }
		if (line != NULL)
			ft_strdel(&line);
		(corewar->currentline)++;
	}
    return (1);
}