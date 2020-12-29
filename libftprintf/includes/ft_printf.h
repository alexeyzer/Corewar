/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 12:20:55 by alexzudin         #+#    #+#             */
/*   Updated: 2020/10/15 16:16:34 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>

typedef struct	s_flag
{
	int		p;
	int		m;
	int		o;
	int		pr;
	int		z;
	int		per;
}				t_flag;

typedef struct	s_printf
{
	int			helper;
	int			m;
	int			lenforpr;
	int			havewidth;
	int			sizecorrect;
	int			hp;
	char		t;
	t_flag		*f;
	int			w;
	int			precision;
	char		*r;
}				t_print;

int				ft_printf(const char *format, ...);
void			checkforflag(char **format, t_print *print);
t_print			*print_init(t_print *new_print);
int				exits(t_print **end_print);
int				checkforextra(char a, char **f, t_print **p, va_list list);
int				secondcheck(char a, char **f, t_print **print, va_list list);
int				checklast(char **format, char a, t_print **print,
	va_list list);
int				checklastlast(char **f, char a, t_print **print);
void			work_with_int(t_print *print, va_list list, int *count);
void			work_with_unsigned_int(t_print *print, va_list list, int *c);
void			work_with_float(t_print *print, va_list list, int *count);
void			work_with_char(t_print *print, va_list list, int *count);
void			work_with_string(t_print *print, va_list list, int *count);
void			work_with_octaedral(t_print *print, va_list list, int *count);
void			work_with_hectaedral(t_print *print, va_list list, int *count);
unsigned int	check_nbr_length(long long int nbr, int base, t_print *p);
void			look_at_w(unsigned int nl, t_print *p, void *d);
void			printing(unsigned int ln, char sy, t_print *p, void *d);
void			outputdata(void *data, t_print *p);
void			outputdata2(void *data, t_print *p);
void			putlesswdth(char a, t_print *p);
void			checkprd(int *len, int precision, t_print *p, int nbr);
char			*edits(char *s, unsigned int pr, t_print *p, unsigned int *ln);
unsigned int	lenunsigned(unsigned long long int n);
int				cfo(unsigned long long int a, t_print *p, int base, int pres);
void			puthectadel(unsigned long long int nbr, char a);
void			work_with_percent(t_print *print, int *count);
void			buvford(t_print *print, va_list list, int *count);
void			ft_putnbrlld(long long int n);
long long int	dbuffer(t_print *p, va_list list);
unsigned int	check_nbr_lengthshort(short int nbr, short int b, t_print *p);
unsigned int	checklength(void *nbr, int base, t_print *p);
int				isit(void *nbr, t_print *p);
void			itis(void *nbr, t_print *p);
long long int	gethecta(t_print *p, va_list list);
int				countcocta(void *a, t_print *p, int base, int pres);
void			putlongint(unsigned long long int nbr);
void			modul(t_print *p, int *w);
void			freeinit(t_print **print);
void			work_with_pointer(t_print *print, va_list list, int *count);
void			ft_putfloat(long double nbr, t_print *print);
t_print			*clear_init(t_print **new_print);
int				l(t_print *p);
void			work_with_print(t_print **print, va_list list, int *count);
void			putstr(char const *s, int n, t_print *print);

#endif
