/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:24:14 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/21 14:20:54 by alexzudin        ###   ########.fr       */
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

    status = read(fd, buff, count);
    if (status < count)
        exit(-1);
    result = bytecode_to_int(buff, count);
    return (result);
}

void read_char(int fd, int count, char *dest)
{
    char        buff[count];
    int         status;


    status = read(fd, buff, count);
    if (status < count)
        exit(-1);
    ft_memmove(dest, buff, count);
}

void read_code(int fd, int sizeofexec, t_champ *champ)
{
    unsigned char    *buff;
    int     status;
    unsigned char a;

    if (!(buff = (unsigned char*)malloc(sizeof(unsigned char) * sizeofexec)))
        exit(-1);//не выделилась память
    status = read(fd, buff, sizeofexec);
    if (status < sizeofexec || read(fd, &a, 1) > 0)
        exit(-1);//считано меньше байтов чем заявленно или за исполняемым кодом присутствуют еще символы
    champ->execcode = buff;
}

t_champ *createchamp()
{
    t_champ *newchamp;

    newchamp = NULL;
    newchamp = (t_champ*)malloc(sizeof(t_champ));
    newchamp->inf = (t_header*)malloc(sizeof(t_header));
    newchamp->execcode = NULL;
    newchamp->number = 100;
    newchamp->color = 'c';
    return (newchamp);
}

void champ_parse(char *filename, t_field *field)
{
    int fd;

    if (field->now->nowchamp == NULL)
    {
        field->now->nowchamp = createchamp();
        field->now->nowchamp->number = getmin(field);
    }   
    fd = open(filename, O_RDONLY);
    if (read_int(fd, 4) != COREWAR_EXEC_MAGIC)
        exit(-1);//маджик неправильный
    read_char(fd, PROG_NAME_LENGTH, field->now->nowchamp->inf->prog_name);
    if (read_int(fd, 4) != 0)
        exit(-1);//отсутсвует 0 в виде 4 байт
    field->now->nowchamp->inf->prog_size =read_int(fd, 4);
    if (field->now->nowchamp->inf->prog_size > CHAMP_MAX_SIZE)
        exit(-1);//размер исполняемого кода больше максимума. какой минимум?s
    read_char(fd, COMMENT_LENGTH, field->now->nowchamp->inf->comment);
    if (read_int(fd, 4) != 0)
        exit(-1);//отсутсвует 0 в виде 4 байт
    read_code(fd, field->now->nowchamp->inf->prog_size, field->now->nowchamp);
    field->now =  addchamtolist(field->now);
    close(fd);
}