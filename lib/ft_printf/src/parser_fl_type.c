/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fl_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 16:16:54 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 16:17:01 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*flag_parser(const char *s, t_env *env)
{
	while (ft_strchr("#0-+ ", *s) && *s)
	{
		if (*s == '#')
			env->hash_flag = 1;
		else if (*s == '0')
			env->zero_flag = 1;
		else if (*s == '-')
			env->minus_flag = 1;
		else if (*s == '+')
			env->plus_flag = 1;
		else if (*s == ' ')
			env->space_flag = 1;
		++s;
	}
	return (s);
}

const char	*p_parser(const char *s, t_env *env, va_list ap)
{
	int garbage;

	if (*s == '.')
	{
		env->p_flag = 1;
		++s;
	}
	while (*s >= '0' && *s <= '9' && env->p_flag)
	{
		if (!(env->p))
			env->p = ft_atoi(s);
		++s;
	}
	if (*s == '*' && env->p_flag)
	{
		if (!env->p)
			env->p = va_arg(ap, int);
		else
			garbage = va_arg(ap, int);
		if (env->p < 0)
			env->p_flag = 0;
		++s;
	}
	return (s);
}

const char	*c_parser(const char *s, t_env *env)
{
	static char key[] = "cspdouxXf%";

	if (*s && (ft_strchr(key, *s) || *s == 'i'))
	{
		env->c = ft_strchr(key, *s) - key;
		if (*s == 'i')
			env->c = 3;
		env->valid = 1;
		++s;
	}
	return (s);
}
