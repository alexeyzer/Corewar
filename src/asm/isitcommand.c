/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isitcommand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:56:17 by alexzudin         #+#    #+#             */
/*   Updated: 2021/02/03 15:49:09 by aguiller         ###   ########.fr       */
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
			if (line[j] == table[i].name[j])
				j++;
			else
				break ;
		}
		if ((line[j] == ' ' || line[j] == '\t' || line[j] == DIRECT_CHAR ||  line[j] == '-') && table[i].name[j] == '\0')
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
	if (now == table[numcommand].countofparams - 1)
	{
		while(line[i] !=  ' ' && line[i] !=  '\t' && line[i] != '\n')
			i++;
		if (correctend(&(line[i])) == -1)
			return (-1);
		else
			return (1);
	}
	else if (now < table[numcommand].countofparams - 1)
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

int		parsecommandsargstostruct(t_corewar *c, char *l, int num, int now)
{
	int i;

	i = 0;
	if (c->now->command == NULL)
		c->now->command = createcommand(num);
	while(l[i] ==  ' ' || l[i] ==  '\t')
		i++;
	if (l[i] == 'r' && ((table[num].typeparams[now] & T_REG) > 0))
		connecttoasm(c, now, &(l[i]), T_REG);
	else if (l[i] == DIRECT_CHAR && ((table[num].typeparams[now] & T_DIR) > 0))
		connecttoasm(c, now,  &(l[i]), T_DIR);
	else if ((l[i] == LABEL_CHAR || ft_isdigit(l[i]) == 1 || l[i] == '-') && ((table[num].typeparams[now] & T_IND) > 0))
		connecttoasm(c, now,  &(l[i]), T_IND);
	else
		return (-1);
	return (expectations(l, num, now));
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
	while (now < table[numcommand].countofparams)
	{
		if ((j = parsecommandsargstostruct(corewar, &(line[i]), numcommand, now)) > 0)
			i = i + j;
		else
			exitcorewar(&corewar, "Error with command argument", corewar->currentline, line);
		now++;
	}
	corewar->now->command->online = corewar->currentline;
	addcommand(corewar);
	return (1);
}