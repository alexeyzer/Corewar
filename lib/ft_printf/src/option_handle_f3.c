/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_handle_f3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 19:10:53 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 19:10:58 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_f_not_a_num(t_env *env)
{
	env->p = 0;
	env->p_flag = 1;
	env->zero_flag = 0;
	env->hash_flag = 0;
}

void	flag_manager_f(long double f, t_env *env)
{
	if (not_a_num(f) || infinity(f))
	{
		flag_f_not_a_num(env);
		if (not_a_num(f))
		{
			env->plus_flag = 0;
			env->not_a_num = 1;
		}
		else
		{
			env->infinity = 1;
			if (f == -(1.0 / 0))
				env->negativ = 1;
		}
	}
	if (env->minus_flag)
		env->zero_flag = 0;
	if (env->plus_flag)
		env->space_flag = 0;
	if (!env->p_flag)
	{
		env->p_flag = 1;
		env->p = 6;
	}
}

void	free_f(t_env *env, char *big_s, char *little_s)
{
	if (!env->infinity && !env->not_a_num)
	{
		free(big_s);
		free(little_s);
	}
}
