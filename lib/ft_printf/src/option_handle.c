/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 19:09:53 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 19:09:59 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long int			handle_signed_mod(t_env *env, va_list ap)
{
	long long int n;

	if (env->mod == LL)
		n = va_arg(ap, long long int);
	else if (env->mod == L)
		n = va_arg(ap, long int);
	else if (env->mod == H)
		n = (short int)va_arg(ap, int);
	else if (env->mod == HH)
		n = (char)va_arg(ap, int);
	else
		n = (int)va_arg(ap, int);
	return (n);
}

unsigned long long int	handle_unsigned_mod(t_env *env, va_list ap)
{
	unsigned long long int n;

	if (env->mod == LL)
		n = va_arg(ap, unsigned long long int);
	else if (env->mod == L)
		n = va_arg(ap, unsigned long int);
	else if (env->mod == H)
		n = (unsigned short int)va_arg(ap, unsigned int);
	else if (env->mod == HH)
		n = (unsigned char)va_arg(ap, unsigned int);
	else
		n = (unsigned int)va_arg(ap, unsigned int);
	return (n);
}

char					set_sign(long long int n, t_env *env)
{
	char sign;

	sign = env->space_flag ? ' ' : '+';
	if (n < 0)
	{
		sign = '-';
		env->negativ = 1;
	}
	return (sign);
}

void					flag_manager(t_env *env)
{
	if (env->p_flag || env->minus_flag)
		env->zero_flag = 0;
	if (env->plus_flag)
		env->space_flag = 0;
}

void					pad_env(t_env *env, int len, int b_len, int seg)
{
	if (!env->zero_flag && !env->minus_flag && env->width >
		b_len && seg == START)
		write_padding(env->width - b_len, ' ');
	else if (!env->zero_flag && env->minus_flag && env->width >
		b_len && seg == END)
		write_padding(env->width - b_len, ' ');
	else if (seg == ZEROS)
	{
		if (env->p_flag)
			write_padding(env->p > len ? env->p - len : 0, '0');
		else if (env->zero_flag && env->width)
			write_padding(env->width > b_len ? env->width - b_len : 0, '0');
	}
}
