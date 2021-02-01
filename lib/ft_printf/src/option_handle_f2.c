/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_handle_f2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 19:10:29 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 19:10:34 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	ten_pow(int pow)
{
	long double f;

	f = 1;
	while (pow > 0)
	{
		f = f * 10;
		--pow;
	}
	while (pow < 0)
	{
		f = f / 10;
		++pow;
	}
	return (f);
}

int			str_line_func(char *str)
{
	return ((str[ft_strlen(str) - 1] - '0') % 2);
}

long double	ft_round(long double f, t_env *env)
{
	long double	temp;
	char		*big_s;
	char		*little_s;

	f = f < 0 ? -f : f;
	temp = f * ten_pow(env->p);
	big_s = big_f(temp);
	little_s = little_f(temp, env->p, big_s);
	temp -= pf_atof_helper(big_s);
	free(big_s);
	if (temp > 0.5 || (temp == 0.5 && str_line_func(big_s)))
		f += 0.5 * ten_pow(-env->p);
	return (f);
}

int			not_a_num(long double f)
{
	return (!(f == f));
}

int			infinity(long double f)
{
	if (f == (1.0 / 0.0) || f == -(1.0 / 0.0))
		return (1);
	else
		return (0);
}
