/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:19:33 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/10 17:26:41 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_labels *createlabel(char *line, int i)
{
	t_labels	*init;
	int			j;
	char		*label;
	int			size;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	size = i - j;
	label = ft_strnew(size);
	i = 0;
	while(i < size)
	{
		label[i] = line[j];
		i++;
		j++;
	}
	init = (t_labels*)malloc(sizeof(t_labels));
	init->label = label;
	init->prev = NULL;
	init->next = NULL;
	return (init);
}

void	addlabel(t_corewar *corewar, char *line, int i)
{
	t_labels	*now;

	if (corewar->now->label == NULL)
		corewar->now->label = createlabel(line, i);
	else
	{
		now = corewar->now->label;
		while (now->next != NULL)
			now = now->next;
		now->next = createlabel(line, i);
		now->next->prev = now;
	}
}

int	correctend(char *line)
{
	int i;

	i = 0;
	while(line[i] ==  ' ' || line[i] ==  '\t')
		i++;
	if (line[i] == '\n')
		return (1);
	else if (line[i] == ALT_COMMENT_CHAR || line[i] == COMMENT_CHAR)
	{
		while (line[i] != '\n' && line[i] != '\0')
			i++;
		if (line[i] == '\n')
			return (1);
		else
			return (-1);	
	}
	return (-1);
}

void addcommand(t_corewar *corewar)
{
	t_asm *newasm;

	newasm = initasm();
	corewar->now->next = newasm;
	newasm->prev = corewar->now;
	corewar->now = newasm;
}