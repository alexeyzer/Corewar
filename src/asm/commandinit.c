/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:54:47 by alexzudin         #+#    #+#             */
/*   Updated: 2021/02/02 23:50:57 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_diretcommand *createcommand(int numcommand)
{
	t_diretcommand *head;
	int i;

	i = 0;
	if (!(head = (t_diretcommand*)malloc(sizeof(t_diretcommand))))
		return (NULL);
	head->commandnum = numcommand;
	head->param = (char**)malloc(sizeof(char*) * table[numcommand].countofparams);
	while (i < table[numcommand].countofparams)
	{
		head->param[i] = NULL;
		i++;
	}
	head->paramtransmited = (long int*)malloc(sizeof(long int) * table[numcommand].countofparams);
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
	corewar->now->command->param[now] = argcopy(line);
}