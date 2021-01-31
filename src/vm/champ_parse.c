/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgonzo <cgonzo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:24:14 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/27 15:54:40 by cgonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		bytecode_to_int(unsigned char *byte, int size)
{
	int	result;
	int	sign;
	int	i;

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

int		read_int(int fd, int count, t_field *field)
{
	unsigned char	buff[count];
	int				status;
	int				result;

	status = read(fd, buff, count);
	if (status < count)
		exiter(field, "Error. size of executing code invalid");
	result = bytecode_to_int(buff, count);
	return (result);
}

void	read_char(int fd, int count, char *dest)
{
	char	buff[count];
	int		status;

	status = read(fd, buff, count);
	if (status < count)
		exit(-1);
	ft_memmove(dest, buff, count);
}

void	read_code(int fd, int sizeofexec, t_champ *champ, t_field *field)
{
	unsigned char	*buff;
	int				status;
	unsigned char	a;

	if (!(buff = (unsigned char*)malloc(sizeof(unsigned char) * sizeofexec)))
		exiter(field, "Error. Malloc don't allocate memory");
	champ->execcode = buff;
	status = read(fd, buff, sizeofexec);
	if (status < sizeofexec || read(fd, &a, 1) > 0)
		exiter(field, "Error. size of executing code invalid");
}

void	champ_parse(char *filename, t_field *f)
{
	int fd;

	if (f->now->nowchamp == NULL)
	{
		f->now->nowchamp = createchamp();
		f->now->nowchamp->number = getmin(f);
	}
	fd = open(filename, O_RDONLY);
	if (read_int(fd, 4, f) != COREWAR_EXEC_MAGIC)
		exiter(f, "Error with magic in file");
	read_char(fd, PROG_NAME_LENGTH, f->now->nowchamp->inf->prog_name);
	if (read_int(fd, 4, f) != 0)
		exiter(f, "Error. No NULL in file");
	f->now->nowchamp->inf->prog_size = read_int(fd, 4, f);
	if (f->now->nowchamp->inf->prog_size > CHAMP_MAX_SIZE)
		exiter(f, "Error. Exec size is too big.");
	read_char(fd, COMMENT_LENGTH, f->now->nowchamp->inf->comment);
	if (read_int(fd, 4, f) != 0)
		exiter(f, "Error. No NULL in file");
	read_code(fd, f->now->nowchamp->inf->prog_size, f->now->nowchamp, f);
	f->now = addchamtolist(f->now);
	close(fd);
}
