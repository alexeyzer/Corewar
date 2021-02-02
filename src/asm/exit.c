/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:43:46 by alexzudin         #+#    #+#             */
/*   Updated: 2021/02/02 22:37:36 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int exitn(t_corewar **corewar, char *strtoprint, int online, int nbr)
{
	ft_printf("%s param nbr#%d on line %d\n", strtoprint, nbr, online);
	exitcorewar(corewar, NULL, -1, NULL);
	return (1);
}

void cleanlabel(t_labels **headlabel)
{
	while ((*headlabel)->next != NULL)
	{
		cleanlabel(&((*headlabel)->next));
		(*headlabel)->next = NULL;
	}
	if((*headlabel)->label != NULL)
		free((*headlabel)->label);
	(*headlabel)->label = NULL;
	(*headlabel)->prev = NULL;
	(*headlabel)->next = NULL;
	free((*headlabel));
}

void cleancommand(t_diretcommand *headcommand)
{
	int		i;
	char	*freeline;

	i = 0;
	while (i < table[headcommand->commandnum].countofparams)
	{
		freeline = headcommand->param[i];
		headcommand->param[i] = NULL;
		if (freeline != NULL)
			free(freeline);
		i++;
	}
	if (headcommand->param != NULL)
		free(headcommand->param);
	headcommand->param = NULL;
	if (headcommand->paramtransmited != NULL)
		free(headcommand->paramtransmited);
	headcommand->paramtransmited = NULL;
	free(headcommand);
}

void cleanasm(t_asm **headasm)
{
	while((*headasm)->next != NULL)
	{
		cleanasm(&((*headasm)->next));
		(*headasm)->next = NULL;
	}
	if ((*headasm)->label != NULL)
	{
		cleanlabel(&((*headasm)->label));
		(*headasm)->label = NULL;
	}
	if ((*headasm)->command != NULL)
	{
		cleancommand((*headasm)->command);
		(*headasm)->command = NULL;
	}
	(*headasm)->next = NULL;
	(*headasm)->prev = NULL;
	if (*headasm != NULL)
		free((*headasm));
}

int exitcorewar(t_corewar **corewar, char *strtoprint, int online, char *line)
{

	if (line != NULL)
		ft_strdel(&line);
	if (strtoprint != NULL)
	{
		if (online != -1)
			ft_printf("%s on line %d\n", strtoprint, online);
		else
			ft_printf("%s\n", strtoprint);
	}
	if (*corewar != NULL)
	{
		if ((*corewar)->initial != NULL)
			free((*corewar)->initial);
		(*corewar)->initial = NULL;
		if ((*corewar)->head != NULL)
		{
			cleanasm(&((*corewar)->head));
			(*corewar)->head = NULL;
			(*corewar)->now = NULL;
		}
		free(*corewar);
	}
	exit(0);
}
