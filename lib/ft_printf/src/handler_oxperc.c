/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handler_oxperc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:20:57 by kjamar            #+#    #+#             */
/*   Updated: 2020/11/16 09:34:39 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_o(t_env *env, va_list ap)
{
	unsigned long long int	n;
	char					*s;

	n = handle_unsigned_mod(env, ap);
	s = pf_dtoa_u(n, 8, 0);
	if (env->hash_flag)
	{
		env->p_flag = 1;
		if (!n)
			env->p = MAX(env->p, 1);
		else
			env->p = MAX(env->p, (int)ft_strlen(s) + 1);
	}
	return (write_unsigned(env, n, s, NULL));
}

int		handle_x(t_env *env, va_list ap)
{
	unsigned long long int	n;
	char					*s;
	char					*pointerfl;
	char					hex_char;

	n = handle_unsigned_mod(env, ap);
	hex_char = env->c == 6 ? 'a' : 'A';
	s = pf_dtoa_u(n, 16, hex_char);
	if (env->hash_flag && n)
	{
		pointerfl = env->c == 6 ? "0x" : "0X";
		env->pointerfl = 1;
	}
	return (write_unsigned(env, n, s, (env->pointerfl ? pointerfl : NULL)));
}

int		handle_percent(t_env *env)
{
	if (env->width && !env->zero_flag && !env->minus_flag)
		write_padding(env->width - 1, ' ');
	if (env->width && env->zero_flag && !env->minus_flag)
		write_padding(env->width - 1, '0');
	write(1, "%", 1);
	if (env->width && env->minus_flag)
		write_padding(env->width - 1, ' ');
	return (env->width ? env->width : 1);
}
