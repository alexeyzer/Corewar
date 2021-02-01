/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 19:11:27 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 19:11:34 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		places(unsigned long long n, int base)
{
	int count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		++count;
		n /= base;
	}
	return (count);
}

char	*pf_dtoa_signed(long long int n)
{
	char				*s;
	int					i;

	i = places(n < 0 ? -n : n, 10);
	if (!(s = (char*)ft_memalloc(i + 1)))
		return (NULL);
	if (n == 0)
		s[0] = '0';
	while (n)
	{
		s[--i] = ((n > 0) ? (n % 10) : -(n % 10)) + '0';
		n /= 10;
	}
	return (s);
}

char	*pf_dtoa_u(unsigned long long int n, int base, char c)
{
	char				*s;
	int					i;

	i = places(n, base);
	if (!(s = (char*)ft_memalloc(i + 1)))
		return (NULL);
	if (n == 0)
		s[0] = '0';
	while (n)
	{
		s[--i] = (n % base > 9) ? (n % base - 10 + c) : (n % base + '0');
		n /= base;
	}
	return (s);
}

void	write_padding(int len, char c)
{
	while (len)
	{
		write(1, &c, 1);
		--len;
	}
}

int		write_unsigned(t_env *env, unsigned long long n,
	char *s, char *pointerfl)
{
	int len;
	int b_len;

	flag_manager(env);
	if (env->c == 'o' && env->hash_flag)
	{
		env->p = (env->p_flag && env->p > (int)ft_strlen(s) + 1)
			? env->p : ft_strlen(s) + 1;
		env->p_flag = 1;
	}
	len = env->p_flag && !env->p && n == 0 ? 0 : ft_strlen(s);
	b_len = env_len(env, len, pointerfl);
	pad_env(env, len, b_len, START);
	if (env->pointerfl)
		write(1, pointerfl, ft_strlen(pointerfl));
	pad_env(env, len, b_len, ZEROS);
	write(1, s, len);
	pad_env(env, len, b_len, END);
	free(s);
	return (env->width > b_len ? env->width : b_len);
}
