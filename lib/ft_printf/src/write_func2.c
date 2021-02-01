/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 19:11:43 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 19:11:48 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline int	signed_conv(int c)
{
	if (c == 3)
		return (1);
	else
		return (0);
}

int			env_len(t_env *env, int len, char *pointerfl)
{
	int b_len;

	b_len = (env->p_flag && env->p > len ? env->p : len);
	b_len += (signed_conv(env->c) && (env->space_flag ||
		env->plus_flag || env->negativ) ? 1 : 0);
	if (env->pointerfl)
		b_len += ft_strlen(pointerfl);
	return (b_len);
}
