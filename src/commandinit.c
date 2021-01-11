/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:54:47 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/11 12:58:22 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_diretcommand *createcommand(int numcommand)
{
	t_diretcommand *head;

	if (!(head = (t_diretcommand*)malloc(sizeof(t_diretcommand))))
		return (NULL);
	head->commandnum = numcommand;
	head->param1 = NULL;
	head->param2 = NULL;
	head->param3 = NULL;
	head->typeparams[0] = 0;
	head->typeparams[1] = 0;
	head->typeparams[2] = 0;
	return (head);
}

char *argcopy(char *line)
{
	int		i;
	int		j;
	char	*newline;

	i = 0;
	newline = NULL;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != ',' && line[i] != '\n')
		i++;
	j = i;
	newline = ft_strnew(i);
	i = 0;
	while(i < j)
	{
		newline[i] = line[i];
		i++;
	}
	return (newline);
}

void connecttoasm(t_corewar *corewar, int now, char *line, int type)
{
	corewar->now->command->typeparams[now] = type;
	if (now == 0)
		corewar->now->command->param1 = argcopy(line);
	if (now == 1)
		corewar->now->command->param2 = argcopy(line);
	if (now == 2)
		corewar->now->command->param3 = argcopy(line);
}