/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:09:49 by alexzudin         #+#    #+#             */
/*   Updated: 2020/07/16 17:09:50 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		checkforextra(char a, char **format, t_print **print, va_list list)
{
	if (a == 't')
	{
		(*print)->t = **format;
		(*format)++;
		if ((*print)->t == 'f')
			(*print)->precision = -1;
		return (0);
	}
	if (a == 'f')
	{
		if (**format == '%')
		{
			(*print)->f->per = 1;
			(*format)++;
			return (0);
		}
		checkforflag(format, *print);
		(*format)++;
		return (1);
	}
	return (secondcheck(a, format, print, list));
}

int		secondcheck(char a, char **format, t_print **print, va_list list)
{
	if (a == 'w')
	{
		(*print)->havewidth = 1;
		if (**format == '*')
		{
			(*print)->w = va_arg(list, int);
			while (**format == '*')
				(*format)++;
		}
		else
		{
			(*print)->w = ft_atoi(*format);
			while (**format >= '0' && **format <= '9')
				(*format)++;
		}
		return (1);
	}
	return (checklast(format, a, print, list));
}

int		checklast(char **format, char a, t_print **print, va_list list)
{
	if (a == 'p')
	{
		(*print)->hp = 1;
		(*format)++;
		if (**format == '*')
		{
			(*print)->precision = va_arg(list, int);
			while (**format == '*')
				(*format)++;
		}
		else
		{
			(*print)->precision = ft_atoi(*format);
			while (**format >= '0' && **format <= '9')
				(*format)++;
		}
		return (1);
	}
	return (checklastlast(format, a, print));
}

int		checklastlast(char **format, char a, t_print **print)
{
	if (a == 's')
	{
		(*print)->r[0] = **format;
		if ((**format == 'j' || **format == 'z') && *((*format) + 1) != 'h')
			(*print)->r[0] = 'l';
		if (**format == 'L')
			(*print)->r[1] = **format;
		(*format)++;
		if (**format == 'l' || **format == 'h')
		{
			(*print)->r[1] = **format;
			(*format)++;
		}
		return (1);
	}
	return (exits(print));
}

t_print	*print_init(t_print *new_print)
{
	t_flag	*new_flag;

	new_flag = (t_flag*)malloc(sizeof(t_flag));
	new_print = (t_print*)malloc(sizeof(t_print));
	new_flag->p = 0;
	new_flag->m = 0;
	new_flag->o = 0;
	new_flag->pr = 0;
	new_flag->z = 0;
	new_flag->per = 0;
	new_print->f = new_flag;
	new_print->t = 'e';
	new_print->hp = 0;
	new_print->havewidth = 0;
	new_print->lenforpr = 0;
	new_print->sizecorrect = 0;
	new_print->w = 0;
	new_print->helper = 0;
	new_print->precision = 0;
	new_print->m = 0;
	new_print->r = ft_strnew(2);
	new_print->r[0] = ' ';
	new_print->r[1] = ' ';
	return (new_print);
}
