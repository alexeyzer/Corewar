/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:20:02 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 17:20:09 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pad_env_f(int len, t_env *env, int seg)
{
	if (!env->zero_flag && !env->minus_flag && env->width >
		len && seg == START)
		write_padding(env->width - len, ' ');
	else if (!env->zero_flag && env->minus_flag && env->width >
		len && seg == END)
		write_padding(env->width - len, ' ');
	else if (seg == ZEROS)
	{
		if (env->zero_flag && env->width)
			write_padding(env->width > len ? env->width - len : 0, '0');
	}
}

int		env_len_f(char *big_s, t_env *env)
{
	int len;

	if (env->infinity || env->not_a_num)
		len = 3;
	else
		len = ft_strlen(big_s) + env->p;
	if (env->p > 0 || env->hash_flag)
		len += 1;
	if (env->space_flag || env->plus_flag)
		len += 1;
	return (len);
}

char	set_sign_f(long double f, t_env *env)
{
	char sign;

	sign = env->space_flag ? ' ' : '+';
	if (f < 0)
	{
		sign = '-';
		env->negativ = 1;
	}
	return (sign);
}

int		write_f(t_env *env, char sign, char *big_s, char *little_s)
{
	int len;

	len = env_len_f(big_s, env);
	pad_env_f(len, env, START);
	if (env->space_flag || env->plus_flag || env->negativ)
		write(1, &sign, 1);
	pad_env_f(len, env, ZEROS);
	write(1, big_s, ft_strlen(big_s));
	if (env->p || env->hash_flag)
		write(1, ".", 1);
	write(1, little_s, ft_strlen(little_s));
	pad_env_f(len, env, END);
	return (len);
}

int		handle_f(t_env *env, va_list ap)
{
	long double	f;
	char		*little_s;
	char		*big_s;
	char		sign;
	int			len;

	f = handle_float_mod(env, ap);
	flag_manager_f(f, env);
	sign = set_sign_f(f, env);
	if (!env->infinity && !env->not_a_num)
	{
		f = ft_round(f, env);
		big_s = big_f(f);
		little_s = little_f(f, env->p, big_s);
	}
	else
	{
		big_s = env->infinity ? "inf" : "nan";
		little_s = "";
	}
	len = write_f(env, sign, big_s, little_s);
	free_f(env, big_s, little_s);
	return (MAX(env->width, len));
}
