/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isitcommand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:56:17 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/10 14:56:37 by alexzudin        ###   ########.fr       */
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

int expectations(t_corewar *corewar, char *line, int numcommand, int now)
{
	//expect ' ' but ',' always shoud be here if this is not the last parametr
	//if it is the last paramter we shoud expect '\n'
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

int parsecommandsargstostruct(t_corewar *corewar, char *line, int numcommand, int now)
{
	int i;

	i = 0;
	while(line[i] ==  ' ' || line[i] ==  '\t')
		i++;
	if (line[i] == 'r' && ((commandstable[numcommand].typeparams[now] & T_REG) > 0))
	{
		corewar->fd = corewar->fd;
		ft_printf("workin with register\n");
	}
	else if (line[i] == (char)DIRECT_CHAR && ((commandstable[numcommand].typeparams[now] & T_DIR) > 0))
	{
		ft_printf("workin with direct num\n");
	}
	else if ((line[i] == (char)LABEL_CHAR || ft_isdigit(line[i]) == 1 || line[i] == '-') && ((commandstable[numcommand].typeparams[now] & T_IND) > 0))
	{
		ft_printf("workin with Indirect num\n");
	}
	else
		return (-1);
	return (1);
}

int iscommandcorrect(t_corewar *corewar, char *line, int numcommand, int i)
{
	int now;

	now = 0;
	while((line[i] ==  ' ' || line[i] ==  '\t') && (line[i] != '\n' && line [i] != '\0'))
		i++;
	while (line[i] !=  ' ' && line[i] !=  '\t' && line[i] != DIRECT_CHAR && line[i] != '-')
		i++;
	while (now < commandstable[numcommand].countofparams)
	{
		parsecommandsargstostruct(corewar, &(line[i]), numcommand, now);

		now++;
	}
	return (1);
}