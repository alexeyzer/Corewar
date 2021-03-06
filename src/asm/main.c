/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:49:36 by alexzudin         #+#    #+#             */
/*   Updated: 2021/02/02 22:54:27 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


int checkname2(char *str, int i)
{
	int c;

	c = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
			c = i;
		i++;
	}
	if (c == 0)
		return (-1);
	else
		if (str[c + 1] == 's' && str[c + 2] == '\0')
			return (1);
	return (-1);
}

int checkname(char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			count++;
		i++;
	}
	i = 0;
	while (count > 0)
	{
		if (str[i] == '/')
			count--;
		i++;
	}
	return (checkname2(str, i));
}

t_corewar *initstruct()
{
	t_corewar *newcorewar;

	newcorewar = (t_corewar*)malloc(sizeof(t_corewar));
	newcorewar->initial = (t_header*)malloc(sizeof(t_header));
	newcorewar->head = NULL;
	return (newcorewar);
}

void testfunc(t_corewar *corewar)
{
	t_asm *now;
	
	int i;

	now = corewar->head;
	while(now != NULL && now->command != NULL)
	{
		i = 0;
		ft_printf("%s ", table[now->command->commandnum].name);
		while (i < table[now->command->commandnum].countofparams)
		{
			ft_printf("%d ", (int)(now->command->paramtransmited)[i]);
			i++;
		}
		ft_printf("\n");
		now = now->next;
	}
}


int main(int argc, char **argv)
{
	t_corewar *corewar;

	if (argc != 2)
	{
		ft_printf("Usage: ./asm player.s\n");
		exit(0);
	}
	else
	{
		if (checkname(argv[1]) < 0)
		{
			ft_printf("Our program could work only with .s extension\n");
			exit(0);
		}
		else
		{
			corewar = initstruct();
			validator(argv[1], corewar);
			commandparser(corewar);
			getsizeall(corewar);
			checkallarguments(corewar);
			//testfunc(corewar);
			filewrite(argv[1], corewar);
			exitcorewar(&corewar, NULL, -1, NULL);
		}
	}
	return (0);
}