/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:27:13 by alexzudin         #+#    #+#             */
/*   Updated: 2021/02/03 16:36:55 by aguiller         ###   ########.fr       */
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

typedef struct	s_diretcommand
{
	int					online;
	int					commandnum;
	int                	typeparams[3];
	char				**param;
	long int			*paramtransmited;
}				t_diretcommand;

typedef struct	s_command
{
	char                *name;
	int					code;
    int                 countofparams;
	int                	typeparams[3];
	int					argumentcode;
	int					dir_size;
}				t_command;


static t_command		table[16] = {
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
    t_diretcommand		*command;
	struct s_asm        *next;
    struct s_asm        *prev;
}				t_asm;

typedef struct	s_corewar
{
	t_header			*initial;
	t_asm				*head;
	t_asm				*now;
	int					fd;
	int					fdwrite;
	int					currentline;
	
}				t_corewar;

int				validator(char *filename, t_corewar *corewar);
int exitcorewar(t_corewar **corewar, char *strtoprint, int online, char *line);
void			getnext(char **line, int *i, t_corewar *corewar);
int				isitcomment(char *line);
int				getcurrentstring2(char **line, t_corewar *corewar, int i, int *goin);
int				get_str(const int fd, char **row);
int				commandparser(t_corewar *corewar);
int				isitcommand(char *line, int r);
void			addlabel(t_corewar *corewar, char *line, int i);
int				iscommandcorrect(t_corewar *corewar, char *line, int numcommand, int i);
void			connecttoasm(t_corewar *corewar, int now, char *line, int type);
int				correctend(char *line);
t_asm			*initasm();
void			addcommand(t_corewar *corewar);
t_diretcommand	*createcommand(int numcommand);
void			getsizeall(t_corewar *corewar);
int				exitn(t_corewar **corewar, char *strtoprint, int online, int nbr);
void			checkallarguments(t_corewar *corewar);
void			filewrite(char *name, t_corewar *corewar);
void int_tobytecode(int fd, long int value, int size);
void			writecarg(t_corewar *corewar, t_asm *asme);
long int correctnum(long int num);
#endif
