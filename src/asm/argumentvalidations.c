/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argumentvalidations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:08:40 by alexzudin         #+#    #+#             */
/*   Updated: 2021/02/03 15:45:52 by aguiller         ###   ########.fr       */
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
		//if (nbr == 0)
		//	exitn(&corewar, "Register nbr can't be zero. Error with", now->command->online, n);
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
	realnow = realnow->next;
	while(realnow != NULL)//иддем вниз
	{
		label = realnow->label;
		while (label != NULL)
		{
			if (ft_strcmp(label->label, (&line[i])) == 0)
				return (size);
			label = label->next;
		}
		size = size + realnow->size;
		realnow = realnow->next;
	}
	return (exitn(&corewar, "Invalid label. Error with", corewar->now->command->online, n));
}

int funcme(char *line, t_corewar *corewar, int i)
{
	t_asm *now;
	t_labels *label;

	now = corewar->now;
	label = now->label;
	while (label != NULL)
	{
		if (ft_strcmp(label->label, &(line[i])) == 0)
			return (1);
		label = label->next;
	}
	return (0);
}

double	getadressup(char *line, int i, t_corewar *corewar, int n)
{
	double	size;
	t_asm	*realnow;
	t_labels *label;

	realnow = corewar->now;
	size = 0;
	if (funcme(line, corewar, i) == 1)
		return (0);
	realnow = realnow->prev;
	while(realnow != NULL)//иддем верх
	{
		label = realnow->label;
		while (label != NULL)
		{
			if (ft_strcmp(label->label, &(line[i])) == 0)
				return ((size + realnow->size) * -1);
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
	while (line[i] != '\0' && line[i] != ALT_COMMENT_CHAR && line[i] != COMMENT_CHAR && line[i] != ' ' && line[i] != '\t')
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

long int  checkdir(t_corewar *corewar, char *line, int n, t_asm *now)
{
	int			i;
	long int		result;

	i = 0;
	result = 0;
	if (line[i] == '%')
	{
		i++;
		if (line[i] == ':')
			result = getadressup(line, i + 1, corewar, n);
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
		result = getadressup(line, i + 1, corewar, n);
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