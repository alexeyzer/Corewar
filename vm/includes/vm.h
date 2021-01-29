/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:45:16 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/29 10:55:36 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "op.h"
# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# define MISTAKESYMB -1

# define COLOR
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PINK		"\033[35m"
# define GRBL		"\033[36m"
# define GREY		"\033[37m"
# define NO			"\033[0m"

typedef struct		s_cell
{
	char			color;
	unsigned char	cell;
}					t_cell;

typedef struct		s_champ
{
	t_header		*inf;
	unsigned char	*execcode;
	char			color;
	int				number;
	int				alive;
}					t_champ;

typedef struct		s_champlist
{
	t_champ				*nowchamp;
	struct s_champlist	*prev;
	struct s_champlist	*next;
}					t_champlist;

typedef struct		s_process
{
	int					pos;
	int					idle;
	int					carry;
	char				color;
	int					bytetonextсop;
	int					lastcyclelive;
	int					moved;
	int					cop;
	int					reg[REG_NUMBER];
	t_champlist			*parent;
	struct s_process	*prev;
	struct s_process	*next;
}					t_process;

typedef struct		s_field
{
	int				aff;
	int				dump;
	int				cycle;
	int				checks;
	int				countlive;
	int				cyclecheck;
	int				cycles_to_die;
	int				lastprocesssadlust;
	t_process		*first;
	t_champlist		*champlist;
	t_champlist		*now;
	t_cell			*mass;
}					t_field;

typedef struct		s_command
{
	char			*name;
	int				code;
	int				countofparams;
	int				typeparams[3];
	int				argumentcode;
	int				dir_size;
	int				carry;
	int				cycle;
	void			(*exec)(t_field *, t_process *);
}					t_command;

int					getcountoflist(t_champlist *head);
int					is_key_a(char *curr, t_field *field);
void				champ_parse(char *filename, t_field *field);
t_champlist			*isitbusy(t_champlist *head, int number);
t_champlist			*addchamtolist(t_champlist *now);
t_field				*init(int i);
void				place(t_field *field);
void				field_print(t_field *field);
t_champ				*createchamp();
void				makecolor(t_champlist *head);
void				currectnum(t_field *field);
int					getmin(t_field *field);
t_process			*init_proc(t_field *field);
int					bytecode_to_int(unsigned char *byte, int size);
void				deleteallproc(t_field *field);
void				check(t_field *field);
void				play(t_field *field);
int					getcyclesforcop(t_process *now);
void				executer(t_field *field, t_process *process);
void				mainexecuter(t_field *field, t_process *process);
int					istypecorrectnoargreg(t_field *field, t_process *process);
int					skipnoarg(t_process *process);
void				printplayers(t_field *field);
void				simpleresult(t_field *field);
void				destroy_field (t_field **field);
int					exiter(t_field *field, char *strtoprint);
int					map_to_int(t_field *field, int pos, int size);
void				live(t_field *field, t_process *process);
void				zjmp(t_field *field, t_process *process);
int					gettype(signed char argumentcode, int number);
int					res(int *bytes, int type, t_field *field, t_process *p);
void				int_to_map(t_field *field, int pos, int size, int data);
void				color_to_map(t_field *field, int pos, int size, char color);
void				st(t_field *field, t_process *process);
void				for_fork(t_field *field, t_process *parent, int adr);
void				my_fork(t_field *field, t_process *process);
void				aff(t_field *field, t_process *process);
void				helpfunc(int reg, int p1, int p2, t_process *process);
void				multiplyfunc(t_field *field, t_process *process);
void				arith(t_field *field, t_process *process);
void				load(t_field *field, t_process *process);
void				ldi(t_field *field, t_process *process);
void				lld(t_field *field, t_process *process);
t_champ				*createchamp();
int					calcpos(int pos);
t_process			*createproc(t_champlist *parent, int num);
t_process			*becomelast(t_process *head);
int					countoflivepc(t_field *field);
int					checkmystake(t_process *p, int result, int i);
int					issamelustlive(t_field *field, int max);
void				sti(t_field *field, t_process *process);
signed char		onebyte(t_field *field, int pos);

static t_command	g_table[16] = {
	{
		.name = "live",
		.code = 0x01,
		.countofparams = 1,
		.typeparams = {T_DIR, 0, 0},
		.dir_size = 4,
		.argumentcode = 0,
		.carry = 0,
		.cycle = 10,
		.exec = &live,
	},
	{
		.name = "ld",
		.code = 0x02,
		.countofparams = 2,
		.typeparams = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
		.argumentcode = 1,
		.carry = 1,
		.cycle = 5,
		.exec = &load,
	},
	{
		.name = "st",
		.code = 0x03,
		.countofparams = 2,
		.typeparams = {T_REG, T_REG | T_IND, 0},
		.dir_size = 4,
		.argumentcode = 1,
		.carry = 0,
		.cycle = 5,
		.exec = &st,
	},
	{
		.name = "add",
		.code = 0x04,
		.countofparams = 3,
		.typeparams = {T_REG, T_REG, T_REG},
		.dir_size = 4,
		.argumentcode = 1,
		.carry = 1,
		.cycle = 10,
		.exec = &arith,
	},
	{
		.name = "sub",
		.code = 0x05,
		.countofparams = 3,
		.typeparams = {T_REG, T_REG, T_REG},
		.dir_size = 4,
		.argumentcode = 1,
		.carry = 1,
		.cycle = 10,
		.exec = &arith,
	},
	{
		.name = "and",
		.code = 0x06,
		.countofparams = 3,
		.typeparams = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
		.argumentcode = 1,
		.carry = 1,
		.cycle = 6,
		.exec = &multiplyfunc,
	},
	{
		.name = "or",
		.code = 0x07,
		.countofparams = 3,
		.typeparams = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
		.argumentcode = 1,
		.carry = 1,
		.cycle = 6,
		.exec = &multiplyfunc,
	},
	{
		.name = "xor",
		.code = 0x08,
		.countofparams = 3,
		.typeparams = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
		.argumentcode = 1,
		.carry = 1,
		.cycle = 6,
		.exec = &multiplyfunc,
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.countofparams = 1,
		.typeparams = {T_DIR, 0, 0},
		.dir_size = 2,
		.argumentcode = 0,
		.carry = 0,
		.cycle = 20,
		.exec = &zjmp,
	},
	{
		.name = "ldi",
		.code = 0x0A,
		.countofparams = 3,
		.typeparams = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.dir_size = 2,
		.argumentcode = 1,
		.carry = 0,
		.cycle = 25,
		.exec = &ldi,
	},
	{
		.name = "sti",
		.code = 0x0B,
		.countofparams = 3,
		.typeparams = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.dir_size = 2,
		.argumentcode = 1,
		.carry = 0,
		.cycle = 25,
		.exec = &sti,
	},
	{
		.name = "fork",
		.code = 0x0C,
		.countofparams = 1,
		.typeparams = {T_DIR, 0, 0},
		.dir_size = 2,
		.argumentcode = 0,
		.carry = 0,
		.cycle = 800,
		.exec = &my_fork,
	},
	{
		.name = "lld",
		.code = 0x0D,
		.countofparams = 2,
		.typeparams = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
		.argumentcode = 1,
		.carry = 1,
		.cycle = 10,
		.exec = &lld,
	},
	{
		.name = "lldi",
		.code = 0x0E,
		.countofparams = 3,
		.typeparams = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.dir_size = 2,
		.argumentcode = 1,
		.carry = 1,
		.cycle = 50,
		.exec = &ldi,
	},
	{
		.name = "lfork",
		.code = 0x0F,
		.countofparams = 1,
		.typeparams = {T_DIR, 0, 0},
		.dir_size = 2,
		.argumentcode = 0,
		.carry = 0,
		.cycle = 1000,
		.exec = &my_fork,
	},
	{
		.name = "aff",
		.code = 0x10,
		.countofparams = 1,
		.typeparams = {T_REG, 0, 0},
		.dir_size = 4,
		.argumentcode = 1,
		.carry = 0,
		.cycle = 2,
		.exec = &aff,
	}
};

#endif
