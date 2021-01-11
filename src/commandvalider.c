/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandvalider.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 08:32:22 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/11 22:07:14 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_asm	*initasm()
{
	t_asm	*head;

	head = (t_asm*)malloc(sizeof(t_asm));
	head->command = NULL;
	head->size = 0;
	head->next = NULL;
	head->prev = NULL;
	head->label = NULL;
	return (head);
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
		if (i == 0)
			exitcorewar(&corewar, "Error, there is no symbols for Label", corewar->currentline, line);
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
		}
		else
			exitcorewar(&corewar, "Error with syntax after label", corewar->currentline, line);
	}
}

int		commandparser(t_corewar *corewar)
{
	char	*line;
	int		i;

	corewar->head = initasm();
	corewar->now = corewar->head;
    while	(get_str(corewar->fd, &line) > 0)
	{
		ft_printf("%s", line);
        if (isitcomment(line) == 0 && *line != '\n')
        {
			if ( (i = isitlabel(corewar, line)) > 0)
				afterlabel(corewar, line, i);
			else if ((i = isitcommand(line, 0)) >= 0)
				iscommandcorrect(corewar, line, i, 0);
			else
				exitcorewar(&corewar, "Syntax error" , corewar->currentline, line);
        }
		if (line != NULL)
			ft_strdel(&line);
		(corewar->currentline)++;
	}
    return (1);
}