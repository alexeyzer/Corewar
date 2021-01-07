/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 15:28:45 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/07 21:06:34 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int getcurrentstring(char **line, t_corewar *corewar, int i, int *goin)
{
	int j;

	j = 0;
	while ((*line)[i] == ' ')
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
				exitcorewar(&corewar, "error with lenght of prog name", corewar->currentline);
		}
		*goin = *goin & 1;
	}
	else
		exitcorewar(&corewar, "error with name_cmd_string", corewar->currentline);
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
		checknameorcomment2(line, corewar, goin);
	return (1);
}

int statchekin(t_corewar *corewar)
{
    char *line;
	int goin;

	goin = 3;
    while	(get_str(corewar->fd, &line) > 0 && goin != 0)//ожидаю либо comment либо name of player// пробелы?
	{
		ft_printf("%s", line);
		if (*line == '\0')
            continue ;
        else if (isitcomment(line) == 0)
        {
            checknameorcomment(&line, corewar, &goin);
        }
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
    {
        ft_printf("%s", "some error ocured with file");
        return (-1);
    }
    else
    {
		corewar->fd = fd;
		corewar->currentline = 1;
        statchekin(corewar);
        return (0);
    }
    return (-1);
}