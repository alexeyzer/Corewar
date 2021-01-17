/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:40:11 by alexzudin         #+#    #+#             */
/*   Updated: 2020/07/15 09:51:14 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				work_with_int(t_print *print, va_list list, int *count)
{
	long long int	nbr;
	int				len;

	nbr = dbuffer(print, list);
	if (isit(&nbr, print) == 1)
		print->m = 1;
	if (print->w < 0)
	{
		print->w *= -1;
		print->f->m = 1;
	}
	len = checklength(&nbr, 10, print);
	checkprd(&len, print->precision, print, nbr);
	if (print->w > len)
		*count = *count + print->w;
	else
		*count = *count + len;
	if (((print->f->pr == 1 && print->m == 0
	&& print->f->p == 0))
	&& ((print->precision >= print->w) || ((print->precision < print->w)
	&& print->w <= len)))
		*count = *count + 1;
	look_at_w(len, print, &nbr);
}

long long int		dbuffer(t_print *p, va_list list)
{
	long long int	lld;
	signed char		a;

	if ((p->r[0] == ' ' && p->r[1] == ' ')
	|| (p->r[0] == 'l' && p->r[1] == 'h'))
		return ((int)va_arg(list, int));
	if (p->r[0] == 'l' && p->r[1] == ' ')
		return ((long int)va_arg(list, long int));
	if ((p->r[0] == 'l' && p->r[1] == 'l')
	|| ((p->r[0] == 'j' || p->r[0] == 'z')
	&& p->r[1] == 'h'))
		return ((long long int)va_arg(list, long long int));
	if (p->r[0] == 'h' && p->r[1] == ' ')
		return ((short int)va_arg(list, int));
	if (p->r[0] == 'h' && p->r[1] == 'h')
	{
		a = (signed char)va_arg(list, int);
		lld = (int)a;
		return ((int)lld);
	}
	return (0);
}

unsigned int		checklength(void *nbr, int base, t_print *p)
{
	if ((p->r[0] == ' ' && p->r[1] == ' ')
		|| (p->r[0] == 'l' && p->r[1] == 'h'))
		return (check_nbr_length(*((int*)nbr), base, p));
	else if (p->r[0] == 'h' && p->r[1] == ' ')
		return (check_nbr_length(*((short int*)nbr), (short int)base, p));
	else if (p->r[0] == 'h' && p->r[1] == 'h')
		return (check_nbr_length(*((signed char*)nbr), base, p));
	else if (p->r[0] == 'l' && p->r[1] == ' ')
		return (check_nbr_length(*((long int*)nbr), base, p));
	else if ((p->r[0] == 'l' && p->r[1] == 'l') || ((p->r[0] == 'j'
	|| p->r[0] == 'z') && p->r[1] == 'h'))
		return (check_nbr_length(*((long long int*)nbr), base, p));
	return (0);
}

unsigned int		check_nbr_length(long long int nbr, int base, t_print *p)
{
	unsigned int			len;
	unsigned long long int	n;

	len = 0;
	if (nbr >= 0 && p->f->p == 1)
		len++;
	if (nbr == 0)
		return (len + 1);
	if (nbr < 0)
	{
		n = nbr * -1;
		len++;
	}
	else
		n = nbr;
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

int					isit(void *nbr, t_print *p)
{
	if (((p->r[0] == ' ' && p->r[1] == ' ') || (p->r[0] == 'l'
	&& p->r[1] == 'h')) && p->t != 'f')
	{
		if ((*(int*)nbr) < 0)
			return (1);
	}
	if (p->r[0] == 'l' && p->r[1] == ' ' && p->t != 'f')
	{
		if ((*(long int*)nbr) < 0)
			return (1);
	}
	else if (p->r[0] == 'h' && p->r[1] == ' ' && p->t != 'f')
	{
		if ((*(short int*)nbr) < 0)
			return (1);
	}
	else if (p->r[0] == 'h' && p->r[1] == 'h' && p->t != 'f')
	{
		if ((*(int*)nbr) < 0)
			return (1);
	}
	return (0);
}
