/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 15:34:57 by alexzudin         #+#    #+#             */
/*   Updated: 2020/07/15 10:46:45 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*edits(char *str, unsigned int precision, t_print *p,
	unsigned int *len)
{
	if (str == NULL)
	{
		*len += 6;
		str = "(null)";
	}
	if (precision < *len && p->hp == 1)
	{
		if (precision == 0)
		{
			p->helper = 1;
			*len = 0;
			return (str);
		}
		*len = precision;
	}
	return (str);
}

void	outputu(unsigned long long int n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}

void	putlongint(unsigned long long int nbr)
{
	char					*nbr_hex;
	int						len;
	unsigned long long int	nbr_tmp;

	len = 0;
	nbr_tmp = nbr;
	if (nbr == 0)
		ft_putchar('0');
	while (nbr_tmp)
	{
		nbr_tmp /= 8;
		len++;
	}
	nbr_hex = (char*)(malloc(sizeof(char) * (len + 1)));
	nbr_hex[len] = '\0';
	len--;
	while (len >= 0)
	{
		nbr_hex[len] = '0' + nbr % 8;
		nbr /= 8;
		len--;
	}
	ft_putstr(nbr_hex);
	free(nbr_hex);
}

void	outputdata2(void *data, t_print *p)
{
	if ((p->t == 'd' || p->t == 'i') && p->helper != 1)
		ft_putnbrlld(*((long long int*)data));
	if ((p->t == 'u' || p->t == 'U') && p->helper != 1)
		outputu(*((unsigned long long int*)data));
	if (p->t == 'o' && (p->hp == 0 || p->precision == 0)
			&& p->f->o == 1 && (*((unsigned long int*)data)) != 0)
		ft_putchar('0');
	if (p->t == 'o' && ((p->helper == 1 && p->f->o == 1) || p->helper != 1))
		putlongint(*((unsigned long long int*)data));
	if (p->t == 'x' && p->helper != 1)
		puthectadel(*((unsigned long long int*)data), 'a');
	if (p->t == 'X' && p->helper != 1)
		puthectadel(*((unsigned long long int*)data), 'A');
	if (p->f->per == 1)
		ft_putchar('%');
	if (p->t == 'p' && p->helper != 1)
		puthectadel(*((unsigned long long int*)data), 'a');
	if (p->t == 'f')
		ft_putfloat(*((long double*)data), p);
	if (p->t == 'c')
		ft_putchar(*((char*)data));
	if ((p->t == 's' || p->t == 'S') && p->helper != 1 &&
		((char*)data) != NULL)
		putstr(((char*)data), p->precision, p);
}

int		exits(t_print **end_print)
{
	*end_print = clear_init(end_print);
	return (0);
}
