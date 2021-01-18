/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgonzo <cgonzo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:24:14 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/18 18:12:25 by cgonzo           ###   ########.fr       */
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

void read_code(int fd, size_t sizeofexec, t_champ *champ)
{
    unsigned char    *buff;
    size_t     status;
    unsigned char a;

    if (!(buff = malloc(sizeofexec)))
        exit(-1);//не выделилась память
    status = read(fd, &buff, sizeofexec);
    if (status < sizeofexec || read(fd, &a, 1) > 0)
        exit(-1);//считано меньше байтов чем заявленно или за исполняемым кодом присутствуют еще символы
    a = buff[0];
    //ft_memmove(buff1, buff, sizeofexec);
    champ->execcode = buff;
}

t_champ *createchamp(int counter)
{
    t_champ *newchamp;

    newchamp = NULL;
    newchamp = (t_champ*)malloc(sizeof(t_champ));
    newchamp->first_proc = NULL;
    newchamp->inf = (t_header*)malloc(sizeof(t_header));
    newchamp->execcode = NULL;
    newchamp->number = counter;
    return (newchamp);
}

void champ_parse(char *filename, t_field *field)
{
    int fd;
    t_champ *new;

    if (field->now->place == -1)
        new = createchamp(field->counter);
    else
        new = createchamp(field->now->place);
    field->now->place = new->number;
    fd = open(filename, O_RDONLY);
    if (read_int(fd, 4) != COREWAR_EXEC_MAGIC)
        exit(-1);//маджик неправильный
    read_char(fd, PROG_NAME_LENGTH, new->inf->prog_name);
    if (read_int(fd, 4) != 0)
        exit(-1);//отсутсвует 0 в виде 4 байт
    new->inf->prog_size =read_int(fd, 4);
    if (new->inf->prog_size > CHAMP_MAX_SIZE)
        exit(-1);//размер исполняемого кода больше максимума. какой минимум?
    read_char(fd, COMMENT_LENGTH, new->inf->comment);
    if (read_int(fd, 4) != 0)
        exit(-1);//отсутсвует 0 в виде 4 байт
    read_code(fd, new->inf->prog_size, new);
    field->now->nowchamp = new;
    field->now =  addchamtolist(field->now);
    close(fd);
}