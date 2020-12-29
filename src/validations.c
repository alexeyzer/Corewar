/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 15:28:45 by alexzudin         #+#    #+#             */
/*   Updated: 2020/12/29 18:30:33 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int statchekin(int fd)
{
    char *line;

    
    while (get_next_line(fd, &line) > 0)//ожидаю либо comment либо name of player// пробелы?
	{
        write(1,"1",1);
        ft_printf("%s\n", line);
		if (*line == '\0')
            continue ;
        else
        {
            //specialcheckerfornameandforcomment
        }
        
		ft_strdel(&line);
	}
    return (0);
}

int validator(char *filename)
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
            statchekin(fd);
            return (0);
        }
    return (-1);
}