/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:26:44 by alexzudin         #+#    #+#             */
/*   Updated: 2020/07/15 10:42:24 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print	*clear_init(t_print **new_print)
{
	t_flag	*flagclean;

	if ((*new_print) != NULL)
	{
		flagclean = (*new_print)->f;
		flagclean->p = 0;
		flagclean->m = 0;
		flagclean->pr = 0;
		flagclean->o = 0;
		flagclean->z = 0;
		flagclean->per = 0;
		(*new_print)->t = 'e';
		(*new_print)->m = 0;
		(*new_print)->helper = 0;
		(*new_print)->havewidth = 0;
		(*new_print)->lenforpr = 0;
		(*new_print)->sizecorrect = 0;
		(*new_print)->hp = 0;
		(*new_print)->w = 0;
		(*new_print)->precision = 0;
		(*new_print)->r[0] = ' ';
		(*new_print)->r[1] = ' ';
	}
	return (*new_print);
}

int		check_letter(char **format, t_print **print, va_list list)
{
	if (**format == 'd' || **format == 'f' || **format == 'c' || **format ==
's' || **format == 'S' || **format == 'o' || **format == 'x' || **format == 'X'
	|| **format == 'F' || **format == 'p' || **format == 'u' || **format == 'U'
	|| **format == 'i' || **format == 'Z')
		return (checkforextra('t', format, print, list));
	if (**format == '+' || **format == '-' || **format == '%' || **format ==
		' ' || **format == '#' || **format == '0')
		return (checkforextra('f', format, print, list));
	if ((**format >= '0' && **format <= '9') || **format == '*')
		return (checkforextra('w', format, print, list));
	if (**format == '.' && **(format + 1))
		return (checkforextra('p', format, print, list));
	if (**format == 'h' || **format == 'l' || **format == 'j' ||
		**format == 'z' || **format == 'L')
		return (checkforextra('s', format, print, list));
	return (exits(print));
}

int		parser(va_list list, char *format, int count, t_print **print)
{
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			while (check_letter((&format), print, list) && *format)
				continue;
			work_with_print(print, list, &count);
			clear_init(print);
		}
		else
		{
			ft_putchar(*format);
			count++;
			format++;
		}
	}
	freeinit(print);
	return (count);
}

int		ft_printf(const char *format, ...)
{
	int			count;
	va_list		list;
	t_print		*print;

	print = NULL;
	print = print_init(print);
	if (print->t == 'f')
		print->precision = -1;
	count = 0;
	va_start(list, (char*)format);
	count = parser(list, (char*)format, count, &print);
	va_end(list);
	return (count);
}

void	freeinit(t_print **print)
{
	t_flag	*flagclean;
	char	*a;

	if (*print != NULL)
	{
		a = (*print)->r;
		free(a);
		flagclean = (*print)->f;
		free(flagclean);
		(*print)->f = NULL;
		free(*print);
		*print = NULL;
	}
}
