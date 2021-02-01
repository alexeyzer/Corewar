/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_cspdu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:20:24 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 17:20:32 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_c(t_env *env, va_list ap)
{
	char c;

	c = va_arg(ap, int);
	if (env->width && !env->minus_flag && !env->zero_flag)
		write_padding(env->width - 1, ' ');
	if (env->width && !env->minus_flag && env->zero_flag)
		write_padding(env->width - 1, '0');
	write(1, &c, 1);
	if (env->width && env->minus_flag)
		write_padding(env->width - 1, ' ');
	return (env->width ? env->width : 1);
}

int	handle_s(t_env *env, va_list ap)
{
	char	*s;
	int		len;

	s = va_arg(ap, char*);
	len = s ? ft_strlen(s) : 6;
	if (env->p_flag && env->p < len)
		len = env->p;
	if (env->width && !env->minus_flag && !env->zero_flag
		&& env->width > len)
		write_padding(env->width - len, ' ');
	if (env->width && !env->minus_flag && env->zero_flag
		&& env->width > len)
		write_padding(env->width - len, '0');
	s ? write(1, s, len) : write(1, "(null)", len);
	if (env->width && env->minus_flag && env->width > len)
		write_padding(env->width - len, ' ');
	return (env->width > len ? env->width : len);
}

int	handle_p(t_env *env, va_list ap)
{
	void	*p;
	char	*s;
	int		len;
	int		b_len;

	p = va_arg(ap, void*);
	s = ft_pointertoch(p, 'a');
	env->pointerfl = 1;
	len = (env->p_flag && !env->p && !p ? 0 : ft_strlen(s));
	b_len = env_len(env, len, "0x");
	pad_env(env, len, b_len, START);
	write(1, "0x", 2);
	pad_env(env, len, b_len, ZEROS);
	write(1, s, len);
	pad_env(env, len, b_len, END);
	free(s);
	return (MAX(env->width, b_len));
}

int	handle_d(t_env *env, va_list ap)
{
	long long int	n;
	char			sign;
	char			*s;
	int				len;
	int				b_len;

	n = handle_signed_mod(env, ap);
	s = pf_dtoa_signed(n);
	flag_manager(env);
	sign = set_sign(n, env);
	len = env->p_flag && !env->p && n == 0 ? 0 : ft_strlen(s);
	b_len = env_len(env, len, NULL);
	pad_env(env, len, b_len, START);
	if (n < 0 || env->plus_flag || env->space_flag)
		write(1, &sign, 1);
	pad_env(env, len, b_len, ZEROS);
	write(1, s, len);
	pad_env(env, len, b_len, END);
	free(s);
	return (env->width > b_len ? env->width : b_len);
}

int	handle_u(t_env *env, va_list ap)
{
	unsigned long long int	n;
	char					*s;

	n = handle_unsigned_mod(env, ap);
	s = pf_dtoa_u(n, 10, 0);
	return (write_unsigned(env, n, s, NULL));
}
