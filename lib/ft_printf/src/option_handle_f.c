/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_handle_f.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 18:55:21 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 18:55:30 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	handle_float_mod(t_env *env, va_list ap)
{
	long double f;

	if (env->mod == 4)
		f = va_arg(ap, long double);
	else
		f = (double)va_arg(ap, double);
	return (f);
}

int			count_big_f(long double f)
{
	int count;

	count = 0;
	while (f > 1)
	{
		count++;
		f /= 10;
	}
	return (MAX(count, 1));
}

long double	pf_atof_helper(char *s)
{
	long double f;

	f = 0;
	while (*s)
	{
		f *= 10;
		f += (long double)(*s - '0');
		++s;
	}
	return (f);
}

char		*big_f(long double f)
{
	char		*s;
	char		*ptr;
	int			count;
	int			i;
	long double	temp;

	count = count_big_f(f);
	if (!(s = (char*)ft_memalloc(count + 1)))
		return (NULL);
	ptr = s;
	while (count)
	{
		i = count - 1;
		temp = f;
		while (i--)
			temp /= 10;
		*ptr++ = (int)temp + '0';
		temp = (int)temp;
		while (++i < count - 1)
			temp *= 10;
		f -= temp;
		--count;
	}
	return (s);
}

char		*little_f(long double f, int p, char *big_f)
{
	char	*s;
	int		i;

	i = 0;
	f = f < 0 ? -f : f;
	f -= pf_atof_helper(big_f);
	if (!(s = (char*)ft_memalloc(p + 1)))
		return (NULL);
	while (i < p)
	{
		f *= 10;
		s[i++] = (f > 0) ? (int)f + '0' : '0';
		f -= (int)f;
	}
	return (s);
}
