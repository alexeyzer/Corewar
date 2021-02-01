/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 15:33:16 by alexzudin         #+#    #+#             */
/*   Updated: 2020/07/15 10:40:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	checkforflag(char **format, t_print *print)
{
	if (**format == '+')
		print->f->p = 1;
	if (**format == '-')
		print->f->m = 1;
	if (**format == '#')
		print->f->o = 1;
	if (**format == ' ')
		print->f->pr = 1;
	if (**format == '0')
		print->f->z = 1;
}

void	outputdata(void *d, t_print *p)
{
	if (((p->f->p == 1 && p->f->z == 0 && p->m == 0) || (p->f->p == 1
		&& p->f->z == 1 && p->m == 0 && p->f->m == 1)) && p->t != 'u')
		ft_putchar('+');
	if (p->t == 'p' || (p->t == 'x' && p->f->o == 1 && *((unsigned int*)d)
				!= 0 && (p->f->z == 0 || (p->f->z == 1 && p->f->m == 1))))
		ft_putstr("0x");
	if (p->t == 'X' && p->f->o == 1 && *((unsigned int*)d) != 0
			&& (p->f->z == 0 || (p->f->z == 1 && p->f->m == 1)))
		ft_putstr("0X");
	if (p->m == 1 && ((isit(d, p) == 1 && p->hp == 1)
				|| (p->t == 'f' && p->f->z == 0)))
	{
		ft_putchar('-');
		if (p->t != 'f')
			itis(d, p);
	}
	while (p->lenforpr > 0)
	{
		ft_putchar('0');
		(p->lenforpr)--;
	}
	outputdata2(d, p);
}

void	putlesswdth(char a, unsigned int *w)
{
	ft_putchar(a);
	*w = (*w) - 1;
}

void	checkprd(int *len, int precision, t_print *p, int nbr)
{
	int	count;

	if (p->hp == 1)
	{
		if (precision >= *len)
		{
			if (p->m == 1)
				count = *len - 1;
			else
				count = *len;
			if (p->f->p == 1 && p->m == 0)
				count--;
			p->lenforpr = precision - count;
			*len = *len + p->lenforpr;
		}
		else
		{
			if (precision == 0 && nbr == 0)
			{
				p->helper = 1;
				if (p->f->o != 1)
					(*len)--;
			}
		}
	}
}

void	putcorrect(void *data, t_print *p)
{
	if ((p->r[0] == ' ' && p->r[1] == ' ') || (p->r[0] == 'l'
				&& p->r[1] == 'h'))
		ft_putnbrlld(*((int*)data));
	if (p->r[0] == 'l' && p->r[1] == ' ')
		ft_putnbrlld(*((long int*)data));
	if ((p->r[0] == 'l' && p->r[1] == 'l') || ((p->r[0] == 'j'
					|| p->r[0] == 'z') && p->r[1] == 'h'))
		ft_putnbrlld(*((long long int*)data));
	else if (p->r[0] == 'h' && p->r[1] == ' ')
		ft_putnbrlld(*((short int*)data));
	else if (p->r[0] == 'h' && p->r[1] == 'h')
		ft_putnbrlld(*((int*)data));
}
