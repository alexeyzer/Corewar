/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations_p2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 11:44:23 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/09 16:34:01 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void getnext(char **line, int *i, t_corewar *corewar)
{
	ft_strdel(line);
	get_str(corewar->fd, line);
	corewar->currentline = corewar->currentline + 1;
	*i = 0;
}

int isitcomment(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
		return (1);
	else
		return (0);
}

int getcurrentstring2(char **line, t_corewar *corewar, int i, int *goin)
{
	int j;

	j = 0;
	while ((*line)[i] == ' ')
		i++;
	if ((*line)[i] == '\"' && (((*goin) & 1) == 1))
	{
		i++;
		while((*line)[i] != '\"')
		{
			if ((*line)[i] == '\0')
				getnext(line, &i, corewar);
			else if (j + 1 <= (int)COMMENT_LENGTH)
				corewar->initial->comment[j++] = (*line)[i++];
			else
				exitcorewar(&corewar, "error with lenght of comment lenght", corewar->currentline, *line);
		}
		*goin = *goin & 2;
	}
	else
		exitcorewar(&corewar, "error with COMMENT_CMD_STRING", corewar->currentline, *line);
	return (1);
}