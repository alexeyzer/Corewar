/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:24:14 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/18 11:20:55 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
int	bytecode_to_int(unsigned char *byte, int size)
{
	int     result;
	int     sign;
	int		i;

	result = 0;
	sign = (byte[0] & 0x80);
	i = 0;
	while (size)
	{
        if (sign)
			result += ((byte[size - 1] ^ 0xFF) << (i * 8));
        else
            result += (byte[size - 1] << (i * 8));
		size--;
        i++;
	}
	if (sign)
	    result = ~(result);
	return (result);
}

int read_int(int fd, int count)
{
    unsigned char   buff[count];
    int             status;
    int             result;

    status = read(fd, &buff, count);
    if (status < count)
        exit(-1);
    result = bytecode_to_int(buff, count);
    return (result);
}

void read_char(int fd, int count, char *dest)
{
    char    buff[count];
    int         status;

    status = read(fd, &buff, count);
    if (status < count)
        exit(-1);
    ft_strcpy(dest, buff);
}

t_champ *createchamp(int counter)
{
    t_champ *newchamp;

    newchamp = NULL;
    newchamp = (t_champ*)malloc(sizeof(t_champ));
    newchamp->first_proc = NULL;
    newchamp->inf = (t_header*)malloc(sizeof(t_header));
    newchamp->next = NULL;
    newchamp->number = counter;
    return (newchamp);
}

t_champ *champ_parse(char *filename, t_field *field, int counter)
{
    int fd;
    t_champ *newchamp;

    newchamp = createchamp(counter);
    fd = open(filename, O_RDONLY);
    if (read_int(fd, 4) != COREWAR_EXEC_MAGIC)
        exit(-1);//маджик неправильный
    read_char(fd, PROG_NAME_LENGTH, newchamp->inf->prog_name);
    if (read_int(fd, 4) != 0)
        exit(-1);//отсутсвует 0 в виде 4 байт
    newchamp->inf->prog_size =read_int(fd, 4);
    if (newchamp->inf->prog_size > CHAMP_MAX_SIZE)
        exit(-1);//размер исполняемого кода больше максимума. какой минимум?
    read_char(fd, COMMENT_LENGTH, newchamp->inf->comment);
    if (read_int(fd, 4) != 0)
        exit(-1);//отсутсвует 0 в виде 4 байт
    //чтение кода
    field->dump = 1;
    return (newchamp);
}