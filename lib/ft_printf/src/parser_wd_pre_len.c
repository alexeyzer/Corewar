/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wd_pre_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 16:17:14 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 16:17:19 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			handle_st_wd(t_env *env, va_list ap, int star_flag)
{
	int garbage;

	if (!env->width || !star_flag)
	{
		env->width = va_arg(ap, int);
		if (env->width < 0)
		{
			env->width = -env->width;
			env->minus_flag = 1;
		}
		return (1);
	}
	else
	{
		garbage = va_arg(ap, int);
		return (star_flag);
	}
}

int			mod_parser(const char *s, t_env *env)
{
	char		*ptr;
	static char	key[] = "hlL";

	if (ft_strnstr(s, "hh", 2))
	{
		env->mod = 1;
		return (2);
	}
	else if (ft_strnstr(s, "ll", 2))
	{
		env->mod = 5;
		return (2);
	}
	else if ((ptr = ft_strchr(key, *s)) && *s)
	{
		env->mod = ptr - key + 2;
		return (1);
	}
	return (0);
}

const char	*width_parser(const char *s, t_env *env, va_list ap)
{
	int star_flag;

	star_flag = 0;
	if (*s == '*')
	{
		star_flag = handle_st_wd(env, ap, star_flag);
		++s;
	}
	while (*s >= '0' && *s <= '9')
	{
		if (!(env->width) || star_flag)
			env->width = ft_atoi(s);
		++s;
	}
	if (*s == '*')
	{
		star_flag = handle_st_wd(env, ap, star_flag);
		++s;
	}
	return (s);
}
