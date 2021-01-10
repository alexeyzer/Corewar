/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:54:47 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/10 13:23:31 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_command *createcommand(int numcommand)
{
	t_diretcommand *head;

	if (!(head = (t_command*)malloc(sizeof(t_command))))
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

void connecttoasmreg(t_corewar *corewar, int now, char *line, int numcommand)
{
	if (corewar->now->command == NULL)
		corewar->now->command = createcommand(numcommand);
	corewar->now->command = createcommand(numcommand);
	corewar->now->command->typeparams[now] = T_REG;
	if (now == 0)
		corewar->now->command->param1 = argcopy(line);
	if (now == 1)
		corewar->now->command->param2 = argcopy(line);
	if (now == 2)
		corewar->now->command->param2 = argcopy(line);
}

void connecttoasmdir(t_corewar *corewar, int now, char *line, int numcommand)
{
	if (corewar->now->command == NULL)
		corewar->now->command = createcommand(numcommand);
	corewar->now->command = createcommand(numcommand);
	corewar->now->command->typeparams[now] = T_DIR;
	if (now == 0)
		corewar->now->command->param1 = argcopy(line);
	if (now == 1)
		corewar->now->command->param2 = argcopy(line);
	if (now == 2)
		corewar->now->command->param2 = argcopy(line);
}