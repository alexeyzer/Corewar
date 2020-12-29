/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:49:36 by alexzudin         #+#    #+#             */
/*   Updated: 2020/12/29 18:07:11 by aguiller         ###   ########.fr       */
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


int main(int argc, char **argv)
{
	if (argc != 2)
		ft_printf("Usage: ./asm player.s\n");
	else
	{
		if (checkname(argv[1]) < 0)
		{
			ft_printf("Our program could work only with .s extension\n");
			return (0);
		}
		else
		{
			ft_printf("here we start workin");//сначало надо все проверить и первое это имя или комментарий
			validator(argv[1]);
		}
	}
	return (0);
}