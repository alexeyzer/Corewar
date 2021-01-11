/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:43:46 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/11 18:58:27 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int exitn(t_corewar **corewar, char *strtoprint, int online, int nbr)
{
	ft_printf("%s param nbr#%d on line %d\n", strtoprint, nbr, online);
	exitcorewar(corewar, NULL, -1, NULL);
	return (1);
}

void exitcorewar(t_corewar **corewar, char *strtoprint, int online, char *line)
{
	t_header	*header;

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
		header = (*corewar)->initial;
		if (header != NULL)
		{
			free(header);
			(*corewar)->initial = NULL;
		}
		exit(0);
	}
}
