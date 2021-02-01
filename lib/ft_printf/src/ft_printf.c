/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 15:22:52 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 15:22:58 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_parser(const char *s, t_env *env, va_list ap)
{
	const char *start;

	start = s;
	s = flag_parser(s, env);
	s = width_parser(s, env, ap);
	s = p_parser(s, env, ap);
	s += mod_parser(s, env);
	s = c_parser(s, env);
	return (s - start);
}

int			handler_call(t_env *env, va_list ap)
{
	static int	(*handlers[11])(t_env *env, va_list ap) = {
		&handle_c,
		&handle_s,
		&handle_p,
		&handle_d,
		&handle_o,
		&handle_u,
		&handle_x,
		&handle_x,
		&handle_f
	};
	static int	(*handle_percent_ptr)(t_env *env) = &handle_percent;

	if (env->c == 9)
		return (handle_percent_ptr(env));
	return ((handlers[env->c](env, ap)));
}

int			handle_plain(const char *s)
{
	int		len;
	char	*next;

	next = ft_strchr(s, '%');
	len = next ? next - s : ft_strlen(s);
	write(1, s, len);
	return (len);
}

inline void	zero_write(t_env *env, int *count)
{
	ft_bzero(env, sizeof(*env));
	*count = 0;
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	t_env	env;
	int		count;
	int		temp;

	zero_write(&env, &count);
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format += ft_parser(format + 1, &env, ap) + 1;
			if (env.valid)
				count += handler_call(&env, ap);
			ft_bzero(&env, sizeof(env));
		}
		else
		{
			temp = handle_plain(format);
			format += temp;
			count += temp;
		}
	}
	va_end(ap);
	return (count);
}
