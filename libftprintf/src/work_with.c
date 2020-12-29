/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 10:57:08 by alexzudin         #+#    #+#             */
/*   Updated: 2020/07/15 10:39:43 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	work_with_unsigned_int(t_print *print, va_list list, int *count)
{
	int				len;
	long long int	n;

	len = 0;
	if (print->w < 0)
	{
		print->w *= -1;
		print->f->m = 1;
	}
	n = gethecta(print, list);
	len = countcocta(&n, print, 10, print->precision);
	checkprd(&len, print->precision, print, n);
	look_at_w(len, print, &n);
	if (print->w > len)
		*count = *count + print->w;
	else
		*count = *count + len;
}

void	still_look_at_w(unsigned int len, t_print *p, void *d, char symbol)
{
	printing(len, symbol, p, d);
	if (p->f->m == 0)
		outputdata(d, p);
}

void	look_at_w(unsigned int len, t_print *p, void *d)
{
	char symbol;

	symbol = ' ';
	if (p->f->p == 0 && p->f->pr == 1 && (p->t == 'f'
				|| p->t == 'F' || p->t == 'd' || p->t == 'i') && p->m == 0)
		putlesswdth(' ', p);
	if (p->f->m == 1)
		outputdata(d, p);
	else if (p->f->z == 1)
	{
		if (((p->precision == 0 || p->m == 1) && p->hp != 1)
				|| (p->hp == 1 && p->precision < 0) || p->t == 'f')
			symbol = '0';
		if ((p->m == 1 && p->hp != 1) || l(p))
		{
			if (p->t != 'f')
				itis(d, p);
			ft_putchar('-');
		}
		else if (p->f->p == 1 && p->m == 0 && ((p->w < p->precision) ||
			p->hp == 0))
			ft_putchar('+');
	}
	still_look_at_w(len, p, d, symbol);
}

void	printing(unsigned int len, char symbol, t_print *p, void *d)
{
	int	i;

	if (p->f->o == 1 && symbol == '0' && p->t == 'x' && *(long long int*)d != 0
		&& p->w != 0)
		ft_putstr("0x");
	if (p->f->o == 1 && symbol == '0' && p->t == 'X' && *(long long int*)d != 0
		&& p->w != 0)
		ft_putstr("0X");
	if ((unsigned int)p->w > len)
	{
		i = (unsigned int)p->w - len;
		while (i > 0)
		{
			ft_putchar(symbol);
			i--;
		}
	}
}

int		l(t_print *p)
{
	if (p->t == 'f' && p->m == 1)
		return (1);
	else
		return (0);
}
