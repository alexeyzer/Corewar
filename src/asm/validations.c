/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 15:28:45 by alexzudin         #+#    #+#             */
/*   Updated: 2021/02/02 17:32:50 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int getcurrentstring(char **line, t_corewar *corewar, int i, int *goin)
{
	int j;

	j = 0;
	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;
	if ((*line)[i] == '\"' && ((*goin & 2) == 2))
	{
		i++;
		while((*line)[i] != '\"')
		{
			if ((*line)[i] == '\0')
				getnext(line, &i, corewar);
			else if (j + 1 <= (int)PROG_NAME_LENGTH)
				corewar->initial->prog_name[j++] = (*line)[i++];
			else
				exitcorewar(&corewar, "error with lenght of prog name", corewar->currentline, *line);
		}
		*goin = *goin & 1;
		if (correctend(&((*line)[i + 1])) == -1)
			exitcorewar(&corewar, "error bad characters after name", corewar->currentline, *line);
	}
	else
		exitcorewar(&corewar, "error with name_cmd_string", corewar->currentline, *line);
	return (1);
}

int checknameorcomment2(char **line, t_corewar *corewar, int *goin)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((*line)[i] == ' ')
		i++;
	while((*line)[i] == COMMENT_CMD_STRING[j])
	{
		i++;
		j++;
	}
	if (COMMENT_CMD_STRING[j] == '\0')
		getcurrentstring2(line, corewar, i, goin);
	else
		return (-1);
	return (1);
}

int checknameorcomment(char **line, t_corewar *corewar, int *goin)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while ((*line)[i] == ' ')
		i++;
	while((*line)[i] == NAME_CMD_STRING[j])
	{
		i++;
		j++;
	}
	if (NAME_CMD_STRING[j] == '\0')
		getcurrentstring(line, corewar, i, goin);
	else
		return (checknameorcomment2(line, corewar, goin));
	return (1);
}

int statchekin(t_corewar *corewar)
{
    char *line;
	int goin;

	goin = 3;
    while	(goin != 0 && get_str(corewar->fd, &line) > 0)
	{
        if (isitcomment(line) == 0 && *line != '\n')
            if (checknameorcomment(&line, corewar, &goin) < 0)
				exitcorewar(&corewar, "Syntax error no comment or name", corewar->currentline, line);
		if (line != NULL)
			ft_strdel(&line);
		(corewar->currentline)++;
	}
    return (1);
}

int validator(char *filename, t_corewar *corewar)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd <= 0)
		exitcorewar(&corewar, "some error ocured with file", -1, NULL);
    else
    {
		corewar->fd = fd;
		corewar->currentline = 1;
        statchekin(corewar);
        return (0);
    }
    return (-1);
}