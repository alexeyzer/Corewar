/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:34:51 by alexzudin         #+#    #+#             */
/*   Updated: 2020/07/15 09:50:17 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbrlld(long long int n)
{
	char					a;
	unsigned long long int	i;

	i = 0;
	if (n >= 0)
		i = n;
	if (n < 0)
	{
		i = n * -1;
		ft_putchar('-');
	}
	if (i > 9)
	{
		ft_putnbrlld(i / 10);
		ft_putnbrlld(i % 10);
	}
	else
	{
		a = i + '0';
		ft_putchar(a);
	}
}

void	itis(void *nbr, t_print *p)
{
	if (p->r[0] == ' ' && p->r[1] == ' ')
		(*((long long int*)nbr)) = (*((int*)nbr)) * -1;
	else if (p->r[0] == 'l' && p->r[1] == ' ')
		(*((long long int*)nbr)) = (*((long int*)nbr)) * -1;
	else if (p->r[0] == 'h' && p->r[1] == ' ')
	{
		(*((long long int*)nbr)) = *((short int*)nbr) * -1;
	}
	else if (p->r[0] == 'h' && p->r[1] == 'h')
		(*((long long int*)nbr)) = (*((int*)nbr)) * -1;
}

void	work_with_print2(t_print **print, va_list list, int *count)
{
	char a;

	a = (*print)->t;
	if (a == 's' || a == 'S')
		work_with_string(*print, list, count);
	else if (a == 'o')
		work_with_octaedral(*print, list, count);
	else if (a == 'x')
		work_with_hectaedral(*print, list, count);
	else if (a == 'X')
		work_with_hectaedral(*print, list, count);
	else if (a == 'p')
		work_with_pointer(*print, list, count);
}

void	work_with_print(t_print **print, va_list list, int *count)
{
	char a;

	if (*print)
	{
		a = (*print)->t;
		if ((*print)->f->per == 1)
			work_with_percent(*print, count);
		else if (a == 'Z')
		{
			ft_putchar('Z');
			*count += 1;
		}
		else if (a == 'd' || a == 'i')
			work_with_int(*print, list, count);
		else if (a == 'f' || a == 'F')
			work_with_float(*print, list, count);
		else if (a == 'u' || a == 'U')
			work_with_unsigned_int(*print, list, count);
		else if (a == 'c')
			work_with_char(*print, list, count);
		else
			work_with_print2(print, list, count);
	}
}

void	putstr(char const *s, int n, t_print *print)
{
	int i;

	i = 0;
	if (print->precision <= 0)
		n = ft_strlen(s);
	if (!s)
		return ;
	while (s[i] != '\0' && i < n)
	{
		ft_putchar(s[i]);
		i++;
	}
}
