/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 15:19:11 by kjamar            #+#    #+#             */
/*   Updated: 2020/08/09 15:19:35 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define HH 1
# define H 2
# define L 3
# define LL 5
# define ZEROS 0
# define START 1
# define END 2
# define MAX(x, y) x > y ? x : y

typedef struct			s_env
{
	int					p;
	char				p_flag;
	int					c;
	char				hash_flag;
	char				zero_flag;
	char				minus_flag;
	char				plus_flag;
	char				space_flag;
	int					width;
	char				negativ;
	char				pointerfl;
	char				not_a_num;
	char				infinity;
	char				mod;
	char				valid;
}						t_env;

int						ft_printf(const char *format, ...);
int						handler_call(t_env *env, va_list ap);
int						ft_parser(const char *s, t_env *env, va_list ap);
int						mod_parser(const char *s, t_env *env);
const char				*flag_parser(const char *s, t_env *env);
const char				*width_parser(const char *s, t_env *env, va_list ap);
int						handle_st_wd(t_env *env, va_list ap, int star_flag);
const char				*p_parser(const char *s, t_env *env, va_list ap);
const char				*c_parser(const char *s, t_env *env);
int						handle_c(t_env *env, va_list ap);
int						handle_s(t_env *env, va_list ap);
int						handle_p(t_env *env, va_list ap);
int						handle_d(t_env *env, va_list ap);
int						handle_u(t_env *env, va_list ap);
int						handle_o(t_env *env, va_list ap);
int						handle_x(t_env *env, va_list ap);
int						handle_f(t_env *env, va_list ap);
int						handle_percent(t_env *env);
int						handle_plain(const char *s);
long long int			handle_signed_mod(t_env *env, va_list ap);
unsigned long long int	handle_unsigned_mod(t_env *env, va_list ap);
int						signed_conv(int c);
void					flag_manager(t_env *env);
void					pad_env(t_env *env, int len, int b_len, int seg);
int						env_len(t_env *env, int len, char *pointerfl);
void					pad_env_f(int len, t_env *env, int seg);
int						env_len_f(char *big_s, t_env *env);
char					set_sign_f(long double f, t_env *env);
char					set_sign(long long int n, t_env *env);
void					write_padding(int len, char c);
char					*pf_dtoa_signed(long long int n);
int						places(unsigned long long n, int base);
char					*pf_dtoa_u(unsigned long long int n, int base, char c);
void					zero_write(t_env *env, int *count);
int						not_a_num(long double f);
int						infinity(long double f);
int						str_line_func(char *str);
int						write_unsigned(t_env *env, unsigned long long n,
								char *s, char *pointerfl);
long double				handle_float_mod(t_env *env, va_list ap);
int						count_big_f(long double f);
long double				pf_atof_helper(char *s);
char					*big_f(long double f);
char					*little_f(long double f, int p, char *big_f);
void					flag_manager_f(long double f, t_env *env);
void					flag_f_not_a_num(t_env *env);
int						write_f(t_env *env, char sign,
								char *big_s, char *little_s);
void					free_f(t_env *env, char *big_s, char *little_s);
long double				ten_pow(int pow);
int						str_func(char *str);
long double				ft_round(long double f, t_env *env);

#endif
