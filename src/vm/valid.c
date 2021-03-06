/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:46:20 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/31 12:40:56 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	is_champ(char *filename)
{
	char *filename1;

	filename1 = NULL;
	if (!filename)
		exiter(NULL, "Error with file name ocured");
	if (ft_strlen(filename) < 4)
		return (0);
	filename1 = ft_strsub(filename, ft_strlen(filename) - 4, 4);
	if (!ft_strcmp(filename1, ".cor"))
	{
		if (filename1 != NULL)
			free(filename1);
		return (1);
	}
	if (filename1 != NULL)
		free(filename1);
	return (0);
}

static int	key_dump(char *curr, char *next, t_field *field)
{
	if (!next || !curr)
		return (MISTAKESYMB);
	if ((ft_atoi(next) || ft_strequ(next, "0")) && ft_strequ(curr, "-dump"))
	{
		field->isdump = 1;
		field->dump = ft_atoi(next);
		return (1);
	}
	else if ((ft_atoi(next) || ft_strequ(next, "0")) && ft_strequ(curr, "-d"))
	{
		field->isdump = 2;
		field->dump = ft_atoi(next);
		return (1);
	}
	return (MISTAKESYMB);
}

static int	key_n(char *curr, char *next, char *nextnext, t_field *field)
{
	int			number;
	t_champlist	*change;

	number = 0;
	field->now->nowchamp = createchamp();
	if (curr == NULL || next == NULL || nextnext == NULL)
		return (MISTAKESYMB);
	if ((ft_atoi(next) || ft_strequ(next, "0")) && ft_strequ(curr, "-n"))
	{
		if (!(ft_strequ(next, "0")))
			number = ft_atoi(next);
		if (number > 4 || number < 1 || !(is_champ(nextnext)))
			return (MISTAKESYMB);
		if ((change = isitbusy(field->champlist, number)))
		{
			change->nowchamp->number = getmin(field);
			field->now->nowchamp->number = number;
		}
		else
			field->now->nowchamp->number = number;
		return (1);
	}
	return (MISTAKESYMB);
}

static void	v_and_r(int argc, char **av, int i, t_field *field)
{
	while (i < argc)
	{
		if (is_champ(av[i]))
			champ_parse(av[i], field);
		else
		{
			if (key_dump(av[i], av[i + 1], field) != MISTAKESYMB)
				i += 1;
			else if (is_key_aorv(av[i], field) != MISTAKESYMB)
				i += 0;
			else
			{
				if (key_n(av[i], av[i + 1], av[i + 2], field) == MISTAKESYMB)
					exiter(field, "Error with param parse");
				else
					i += 1;
			}
		}
		i++;
	}
	if (getcountoflist(field->champlist) > MAX_PLAYERS ||\
		getcountoflist(field->champlist) <= 0)
		exiter(field, "Error more then 4 players or less than 1");
}

int			main(int argc, char **argv)
{
	t_field *fild;

	fild = NULL;
	fild = init(0, fild);
	if (argc == 1)
	{
		print_usage();
		return (0);
	}
	v_and_r(argc, argv, 1, fild);
	currectnum(fild);
	makecolor(fild->champlist);
	place(fild);
	make(fild);
	init_proc(fild);
	printplayers(fild);
	play(fild);
	simpleresult(fild);
	destroy_field(&fild);
}
