/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:19:33 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/09 15:43:48 by alexzudin        ###   ########.fr       */
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