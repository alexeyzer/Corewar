/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 20:42:22 by alexzudin         #+#    #+#             */
/*   Updated: 2020/07/15 10:11:10 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			work_with_hectaedral(t_print *p, va_list list, int *count)
{
	long long int	nbr;
	int				len;

	nbr = gethecta(p, list);
	len = countcocta(&nbr, p, 16, p->precision);
	if (nbr == 0 && p->precision == 0 && p->hp == 1)
		len--;
	checkprd(&len, p->precision, p, nbr);
	if (p->f->o == 1 && (p->t == 'x' || p->t == 'X') && nbr != 0)
		len = len + 2;
	if (p->w > len)
		*count = *count + p->w;
	else
		*count = *count + len;
	look_at_w(len, p, &nbr);
	if (((p->f->pr == 1 && p->m == 0 && p->f->p == 0))
			&& p->hp == 0)
		*count = *count + 1;
}

long long int	gethecta(t_print *p, va_list l)
{
	unsigned long long int	d;
	unsigned char			a;

	if (p->r[0] == ' ' && p->r[1] == ' ' && p->t != 'U')
		return ((d = (unsigned int)va_arg(l, unsigned int)));
	if (p->r[0] == 'l' && p->r[1] == ' ')
		return ((d = (unsigned long int)va_arg(l, unsigned long int)));
	if ((p->r[0] == 'l' && p->r[1] == 'l') || p->t == 'U')
		return ((d = va_arg(l, unsigned long long int)));
	if (p->r[0] == 'h' && p->r[1] == ' ')
		return ((d = (unsigned short int)va_arg(l, unsigned int)));
	if (p->r[0] == 'h' && p->r[1] == 'h')
	{
		a = va_arg(l, unsigned int);
		d = (unsigned int)a;
		return ((unsigned int)d);
	}
	return (0);
}

int				countcocta(void *a, t_print *p, int base, int pres)
{
	if (p->r[0] == ' ' && p->r[1] == ' ' && p->t != 'U')
		return (cfo((*((unsigned int*)a)), p, base, pres));
	else if (p->r[0] == 'h' && p->r[1] == ' ' && p->t != 'U')
		return (cfo(*((unsigned short int*)a), p, base, pres));
	else if (p->r[0] == 'h' && p->r[1] == 'h')
		return (cfo(*((unsigned int*)a), p, base, pres));
	else if (p->r[0] == 'l' && p->r[1] == ' ')
		return (cfo(*((unsigned long int*)a), p, base, pres));
	else if ((p->r[0] == 'l' && p->r[1] == 'l') || p->t == 'U')
		return (cfo(*((unsigned long long int*)a), p, base, pres));
	return (0);
}

int				cfo(unsigned long long int a, t_print *p, int b, int pres)
{
	int count;

	count = 0;
	if (a == 0 && pres == 0 && p->hp == 1 &&
	(p->t == 'x' || p->t == 'X'))
		p->helper = 1;
	if (a == 0)
		return (1);
	while (a > 0)
	{
		a /= b;
		count++;
	}
	return (count);
}
