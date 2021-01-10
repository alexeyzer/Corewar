/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isitcommand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:56:17 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/10 17:28:25 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int getnumofcommand(char *line)
{
	int i;
	int j;

	i = 0;
	while (i < 16)
	{
		j = 0;
		while(line[j] != ' ')
		{
			if (line[j] == commandstable[i].name[j])
				j++;
			else
				break ;
		}
		if ((line[j] == ' ' || line[j] == '\t' || line[j] == DIRECT_CHAR) && commandstable[i].name[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

int		expectations(char *line, int numcommand, int now)
{
	int i;

	i = 0;
	while(line[i] ==  ' ' || line[i] ==  '\t')
		i++;
	if (now == commandstable[numcommand].countofparams - 1)
	{
		while(line[i] !=  ' ' && line[i] !=  '\t' && line[i] != '\n')
			i++;
		if (correctend(&(line[i])) == -1)
			return (-1);
		else
			return (1);
	}
	else if (now < commandstable[numcommand].countofparams - 1)
	{
		while(line[i] !=  ',' && line[i] != '\n')
			i++;
		if (line[i] == ',')
			return (i + 1);
		else
			return (-1);
	}
	return (-1);
}

int		isitcommand(char *line, int r)
{
	int i;
	int	num;

	i = r;
	while((line[i] ==  ' ' || line[i] ==  '\t') && (line[i] != '\n' && line [i] != '\0'))
		i++;
	if ((num = getnumofcommand(line + i)) >= 0)
		return (num);
	else
		return (-1);
}

int		parsecommandsargstostruct(t_corewar *corewar, char *line, int numcommand, int now)
{
	int i;

	i = 0;
	while(line[i] ==  ' ' || line[i] ==  '\t')
		i++;
	if (line[i] == 'r' && ((commandstable[numcommand].typeparams[now] & T_REG) > 0))
		connecttoasmreg(corewar, now, &(line[i]), numcommand);
	else if (line[i] == (char)DIRECT_CHAR && ((commandstable[numcommand].typeparams[now] & T_DIR) > 0))
		connecttoasmdir(corewar, now,  &(line[i]), numcommand);
	else if ((line[i] == (char)LABEL_CHAR || ft_isdigit(line[i]) == 1 || line[i] == '-') && ((commandstable[numcommand].typeparams[now] & T_IND) > 0))
		connecttoasmind(corewar, now,  &(line[i]), numcommand);
	else
		return (-1);
	return (expectations(line, numcommand, now));
}

int iscommandcorrect(t_corewar *corewar, char *line, int numcommand, int i)
{
	int		now;
	int		j;

	j = 0;
	now = 0;
	while((line[i] ==  ' ' || line[i] ==  '\t') && (line[i] != '\n' && line [i] != '\0'))
		i++;
	while (line[i] !=  ' ' && line[i] !=  '\t' && line[i] != DIRECT_CHAR && line[i] != '-')
		i++;
	while (now < commandstable[numcommand].countofparams)
	{
		if ((j = parsecommandsargstostruct(corewar, &(line[i]), numcommand, now)) > 0)
			i = i + j;
		else
			exitcorewar(&corewar, "Error with command argument", corewar->currentline, line);
		now++;
	}
	addcommand(corewar);
	return (1);
}