/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 14:03:34 by alexzudin         #+#    #+#             */
/*   Updated: 2020/07/15 10:29:46 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long int	ft_pow(long int nbr, long int n)
{
	long int	tmp;

	tmp = nbr;
	while (n > 1)
	{
		nbr *= tmp;
		n--;
	}
	if (n == 0)
		return (1);
	return (nbr);
}

int			leng(long int nbr)
{
	int			len;
	long int	n;

	len = 0;
	n = nbr;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	if (nbr == 0)
		return (1);
	return (len);
}

void		w(char c, int w)
{
	int	i;

	i = 0;
	while (i < w)
	{
		ft_putchar(c);
		i++;
	}
}

void		ft_putfloat(long double nbr, t_print *print)
{
	long int	br;
	long int	n;

	n = (long int)nbr;
	nbr = nbr - n;
	nbr = nbr * ft_pow(10, print->precision + 1);
	br = (long int)nbr;
	if (br % 10 > 4)
		br += (br % 10 != 9) ? 11 : 1;
	br /= 10;
	if (br / ft_pow(10, print->precision) != 0)
	{
		br %= ft_pow(10, print->precision);
		n++;
	}
	ft_putnbr(n);
	if (print->helper == 0)
	{
		ft_putchar('.');
		w('0', print->precision - leng(br));
		if (br != 0)
			ft_putnbr(br);
	}
}

void		work_with_float(t_print *print, va_list list, int *count)
{
	long double	nbr;
	long int	n;
	long int	l;

	if (print->precision < 0)
		print->precision = 6;
	if (print->precision == 0)
		print->helper = 1;
	nbr = (print->r[1] == 'L') ? va_arg(list, long double) :
		va_arg(list, double);
	n = (nbr > 0) ? (long int)nbr : (long int)(-nbr);
	l = (nbr > 0 && print->f->p == 1) ? leng(n) + 1 : leng(n);
	if (nbr < 0)
	{
		print->m = 1;
		l = l + 1;
		nbr = -nbr;
	}
	else
		print->m = 0;
	*count = *count + print->precision + l + ((print->helper == 1) ?
		0 : 1);
	look_at_w(print->precision + l + ((print->helper == 1) ? 0 : 1),
		print, &nbr);
}
