/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:27:13 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/07 19:36:24 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "op.h"

# define COLOR
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PINK		"\033[35m"
# define GRBL		"\033[36m"
# define GREY		"\033[37m"
# define NO			"\033[0m"

typedef struct	s_command
{
	char                *name;
	int					code;
    int                 countofparams;
	int                	typeparams[3];
	int					argumentcode;
	int					dir_size;
	int					*params;
}				t_command;


static t_command		commandstable[16] = {
	{
		.name = "live",
		.code = 0x01,
		.countofparams = 1,
		.typeparams = {T_DIR, 0, 0},
		.dir_size = 4,
		.argumentcode = 0,
	},
	{
		.name = "ld",
		.code = 0x02,
		.countofparams = 2,
		.typeparams = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
		.argumentcode = 1,
	},
	{
		.name = "st",
		.code = 0x03,
		.countofparams = 2,
		.typeparams = {T_REG, T_REG | T_IND, 0},
		.dir_size = 4,
		.argumentcode = 1,
	},
	{
		.name = "add",
		.code = 0x04,
		.countofparams = 3,
		.typeparams = {T_REG, T_REG, T_REG},
		.dir_size = 4,
		.argumentcode = 1,
	},
	{
		.name = "sub",
		.code = 0x05,
		.countofparams = 3,
		.typeparams = {T_REG, T_REG, T_REG},
		.dir_size = 4,
		.argumentcode = 1,
	},
	{
		.name = "and",
		.code = 0x06,
		.countofparams = 3,
		.typeparams = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
		.argumentcode = 1,
	},
	{
		.name = "or",
		.code = 0x07,
		.countofparams = 3,
		.typeparams = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
		.argumentcode = 1,
	},
	{
		.name = "xor",
		.code = 0x08,
		.countofparams = 3,
		.typeparams = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
		.argumentcode = 1,
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.countofparams = 1,
		.typeparams = {T_DIR, 0, 0},
		.dir_size = 2,
		.argumentcode = 0,
	},
	{
		.name = "ldi",
		.code = 0x0A,
		.countofparams = 3,
		.typeparams = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.dir_size = 2,
		.argumentcode = 1,
	},
	{
		.name = "sti",
		.code = 0x0B,
		.countofparams = 3,
		.typeparams = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.dir_size = 2,
		.argumentcode = 1,
	},
	{
		.name = "fork",
		.code = 0x0C,
		.countofparams = 1,
		.typeparams = {T_DIR, 0, 0},
		.dir_size = 2,
		.argumentcode = 0,
	},
	{
		.name = "lld",
		.code = 0x0D,
		.countofparams = 2,
		.typeparams = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
		.argumentcode = 1,
	},
	{
		.name = "lldi",
		.code = 0x0E,
		.countofparams = 3,
		.typeparams = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.dir_size = 2,
		.argumentcode = 1,
	},
	{
		.name = "lfork",
		.code = 0x0F,
		.countofparams = 1,
		.typeparams = {T_DIR, 0, 0},
		.dir_size = 2,
		.argumentcode = 0,
	},
	{
		.name = "aff",
		.code = 0x10,
		.countofparams = 1,
		.typeparams = {T_REG, 0, 0},
		.dir_size = 4,
		.argumentcode = 1,
	}
};


typedef struct	s_labels
{
	char					*label;
	struct s_labels			*next;
    struct s_labels			*prev;
}				t_labels;

typedef struct	s_asm
{
	t_labels			*label;
    int                 size;
    t_command			*command;
	struct s_asm        *next;
    struct s_asm        *prev;
}				t_asm;

typedef struct	s_corewar
{
	t_header			*initial;
	t_asm				*head;
	t_command			*commandstable;
	int					fd;
	int					currentline;
	
}				t_corewar;

int		validator(char *filename, t_corewar *corewar);
void	exitcorewar(t_corewar **corewar, char *strtoprint, int online);
void	getnext(char **line, int *i, t_corewar *corewar);
int		isitcomment(char *line);
int		getcurrentstring2(char **line, t_corewar *corewar, int i, int *goin);
int		get_str(const int fd, char **row);

/*t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};*/

#endif
