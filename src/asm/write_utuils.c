/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utuils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:53:42 by aguiller          #+#    #+#             */
/*   Updated: 2021/02/02 20:20:04 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void writecarg(t_corewar *corewar, t_asm *asme)
{
	signed char argcode;
	int i;
	int s;

	argcode = 0;
	i = 0;
	s = 6;
	while (i < table[asme->command->commandnum].countofparams)
	{
		if (asme->command->typeparams[i] == T_REG)
			argcode = argcode | REG_CODE << s;
		if (asme->command->typeparams[i] == T_DIR)
			argcode = argcode | DIR_CODE << s;
		if (asme->command->typeparams[i] == T_IND)
			argcode = argcode | IND_CODE << s;
		s -= 2;
		i++;
	}
	int_tobytecode(corewar->fdwrite, argcode, 1);
}

int correctnum(int num)
{
	int i;

	i = 4;
	if (num < 0)
	{
		num = num * -1;
		num = ~num;
		num = num + 1;
	}
	return (num);
}