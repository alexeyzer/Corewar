/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:40:57 by aguiller          #+#    #+#             */
/*   Updated: 2021/02/02 20:14:05 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char *newname(char *name)
{
	int i;
	char *new;
	char *base;

	i = ft_strlen(name);
	base = ft_strsub(name, 0, i - 2);
	new = ft_strjoin(base, ".cor");
	free(base);
	return (new);
}

void int_tobytecode(int fd, int value, int size)
{
	int i;
	signed char a;

	i = 8 * (size - 1);
	while (size > 0)
	{
		a = (unsigned int)((value >> i) & 0xFF);
		write(fd, &a, 1);
		size--;
		i = i - 8;
	}
}

void char_tobytecode(int fd, char *src, int size)
{
	int i;
	int j;
	unsigned char a;

	i = 8 * (size - 1);
	j = 0;
	while (size > 0)
	{
		a = src[j];
		write(fd, &a, 1);
		size--;
		i = i - 8;
		j++;
	}
}

void commands(t_corewar *corewar)
{
	t_asm *now;
	int i;
	int num;

	now = corewar->head;
	while (now != NULL && now->command != NULL)
	{
		i = 0;
		int_tobytecode(corewar->fdwrite, table[now->command->commandnum].code, 1);
		if (table[now->command->commandnum].argumentcode == 1)
			writecarg(corewar, now);
		while (i < table[now->command->commandnum].countofparams)
		{
			num = correctnum((int)now->command->paramtransmited[i]);
			if (now->command->typeparams[i] == T_REG)
				int_tobytecode(corewar->fdwrite, num, 1);
			if (now->command->typeparams[i] == T_IND)
				int_tobytecode(corewar->fdwrite, num, IND_SIZE);
			if (now->command->typeparams[i] == T_DIR)
				int_tobytecode(corewar->fdwrite, num, table[now->command->commandnum].dir_size);
			i++;
		}
		now = now->next;
	}
}

void filewrite(char *name, t_corewar *corewar)
{
	char *new;

	new = newname(name);
	corewar->fdwrite = open(new, O_RDWR | O_TRUNC | O_CREAT, 0600);
	free(new);
	int_tobytecode(corewar->fdwrite, COREWAR_EXEC_MAGIC, 4);
	char_tobytecode(corewar->fdwrite, corewar->initial->prog_name, PROG_NAME_LENGTH);
	int_tobytecode(corewar->fdwrite, 0, 4);
	int_tobytecode(corewar->fdwrite, corewar->initial->prog_size, 4);
	char_tobytecode(corewar->fdwrite, corewar->initial->comment, COMMENT_LENGTH);
	int_tobytecode(corewar->fdwrite, 0, 4);
	commands(corewar);

}