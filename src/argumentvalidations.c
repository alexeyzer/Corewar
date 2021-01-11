/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argumentvalidations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:08:40 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/11 21:06:31 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int  checkreg(t_corewar *corewar, char *line, int n, t_asm *now)
{
	int i;
	int j;
	double	nbr;

	i = 0;
	nbr = 0;
	if(line[i] == 'r')
	{
		i++;
		j = i;
		while (line[i] != '\0')
		{
			if (ft_isdigit(line[i]) == 0)
				exitn(&corewar, "Invalid symbols. Error with", now->command->online, n);
			i++;
		}
		nbr = ft_atoi(&(line[j]));
		if (nbr > 255)
			exitn(&corewar, "max register nbr is 255. Error with", now->command->online, n);
		if (nbr == 0)
			exitn(&corewar, "Register nbr can't be zero. Error with", now->command->online, n);
	}
	else
		exitn(&corewar, "Invalid start symbol. Error with", now->command->online, n);
	return (nbr);
}

double	getadressdown(char *line, int i, t_corewar *corewar, int n)
{
	double	size;
	t_asm	*realnow;
	t_labels *label;

	realnow = corewar->now;
	size = realnow->size;
	while(realnow != NULL)//иддем вниз
	{
		label = realnow->label;
		while (label != NULL)
		{
			if (ft_strcmp(realnow->label->label, (&line[i])))
				return (size);
			label = label->next;
		}
		size = size + realnow->size;
		realnow = realnow->next;
	}
	return (exitn(&corewar, "Invalid label. Error with", corewar->now->command->online, n));
}

double	getadressup(char *line, int i, t_corewar *corewar, int n)
{
	double	size;
	t_asm	*realnow;
	t_labels *label;

	realnow = corewar->now;
	size = realnow->size;
	while(realnow != NULL)//иддем верх
	{
		label = realnow->label;
		while (label != NULL)
		{
			if (ft_strcmp(realnow->label->label, &(line[i])))
				return (size * -1);
			label = label->next;
		}
		size = size + realnow->size;
		realnow = realnow->prev;
	}
	return (getadressdown(line, i, corewar, n));
}

void checknbr(t_corewar *corewar, char *line, int i, int n)
{
	int c;

	c = 0;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) == 0)
		{
			if (line[i] == '-' && c == 0)
				c++;
			else
				exitn(&corewar, "Invalid symbols. Error with", corewar->now->command->online, n);
		}
		i++;
	}
}

int  checkdir(t_corewar *corewar, char *line, int n, t_asm *now)
{
	int			i;
	double		result;

	i = 0;
	result = 0;
	if (line[i] == '%')
	{
		i++;
		if (line[i] == ':')
			result = getadressup(line, 0, corewar, n);
		else
		{
			if (line[i] == '%' && line[i + 1] == '\0')
				exitn(&corewar, "No symbols after %. Error with", now->command->online, n);
			checknbr(corewar, line, i, n);
			result = ft_atoi(&(line[i]));
		}
	}
	else
		exitn(&corewar, "Invalid start symbol. Error with", now->command->online, n);
	if (result >= 4294967296)
		result = result - 4294967296;
	if (result <= -4294967296)
		result = result + 4294967296;
	return (result);
}

int  checkind(t_corewar *corewar, char *line, int n)
{
	int			i;
	double		result;

	i = 0;
	if (line[i] == ':')
		result = getadressup(line, 0, corewar, n);
	else
	{
		checknbr(corewar, line, i, n);
		result = ft_atoi(&(line[i]));
	}
	if (result >= 65536)
		result = result - 65536;
	if (result <= -65536)
		result = result + 65536;
	return (result);
}



void checkargument(t_corewar *corewar, t_asm *now, int nbr)
{

	if (now->command->typeparams[nbr] == T_REG)
		now->command->paramtransmited[nbr] = checkreg(corewar, (now->command->param)[nbr], nbr, now);
	else if (now->command->typeparams[nbr] == T_DIR)
		now->command->paramtransmited[nbr] = checkdir(corewar, (now->command->param)[nbr], nbr, now);
	else if (now->command->typeparams[nbr] == T_IND)
		now->command->paramtransmited[nbr] = checkind(corewar, (now->command->param)[nbr], nbr);
}

void checkallarguments(t_corewar *corewar)
{
	int		c;

	corewar->now = corewar->head;
	while (corewar->now != NULL && corewar->now->command != NULL)
	{
		c = 0;
		while (c  < table[corewar->now->command->commandnum].countofparams)
		{
			checkargument(corewar, corewar->now, c);
			c++;
		}
		corewar->now = corewar->now->next;
	}
}