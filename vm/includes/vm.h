/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:45:16 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/24 17:54:36 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
#include "op.h"
# include "ft_printf.h"
# include "libft.h"
#include <fcntl.h>
#define MISTAKESYMB -1

# define COLOR
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PINK		"\033[35m"
# define GRBL		"\033[36m"
# define GREY		"\033[37m"
# define NO			"\033[0m"

typedef struct	s_cell
{
   // int number;
    char color;
    unsigned char cell;
   // t_cell *prev;
   /// t_cell *next;
}				t_cell;
/*meaning - значение в клетке number - номер prev/next -указатели на соседей*/
typedef struct	s_champ
{
   // int idle;
    t_header *inf;
    //int hp;
    unsigned char *execcode;
    char color;
    int number;
    int alive;
}				t_champ;
/*
нейм - имя
коммент - коммент 
first_proc - ссылка на каретку(ки) 
next - следующий чемпион в списке
у игрока есть N регистров для хранения данных */
typedef struct	s_champlist
{
    t_champ *nowchamp;
    struct	s_champlist *prev;
    struct	s_champlist *next;
}               t_champlist;

typedef struct	s_process
{
    int pos;
    int idle;
    int carry;
    char color;
    int  bytetonextсop;
	int	 lastcyclelive;
	int  moved;
	int	 cop;
    int reg[REG_NUMBER];
	t_champlist *parent;
	struct  s_process *prev;
    struct  s_process *next;
}				t_process;
/*
host - породивший его чемпион
pos -позиция
carry - равен 0 или 1, связан со всеми операциями, 
его значение зависит от результата команды
idle - спит?может выполнить команду только если idle - 0
child - если юзнул форк, для порождения другого процесса
parent - указание на родителя, если нулл -
 процесс первый и порожден в начале игры*/

typedef struct	s_field
{
    int counter;
    int dump;
    int cycle;
	int	checks;
	int countlive;
	int cycles_to_die;
    t_process *first;
    t_process *current;
    t_champlist *champlist;
    t_champlist *now;
    t_cell mass[MEM_SIZE];
}				t_field;
/*counter - количество чемпионов
checks - количество циклов без уменьшения
dump - когда выгрузить состояние поля, если "-1", то выгружать его каждую итерацию
champ_first - корень списка чемпионов
countlive - количество выполненных операций live
  
   */

typedef struct	s_command
{
	char                *name;
	int					code;
    int                 countofparams;
	int                	typeparams[3];
	int					argumentcode;
	int					dir_size;
    int                 carry;
	int					cycle;
}				t_command;

static t_command		table[16] = {
	{
		.name = "live",
		.code = 0x01,
		.countofparams = 1,
		.typeparams = {T_DIR, 0, 0},
		.dir_size = 4,
		.argumentcode = 0,
        .carry = 0,
		.cycle = 10,
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
	}
};

int getcountoflist(t_champlist *head);
t_field *validation_and_reading(int argc, char **argv);
void champ_parse(char *filename, t_field *field);
t_champlist *isitbusy(t_champlist *head, int number);
t_champlist *addchamtolist(t_champlist *now);
t_field        *init();
void place(t_field *field);
void field_print(t_field *field);
t_champ *createchamp();
void makecolor(t_champlist *head);
void currectnum(t_field *field);
int getmin(t_field *field);
void init_proc(t_field *field);
int	bytecode_to_int(unsigned char *byte, int size);
void deleteallproc(t_field *field);
void check(t_field *field);
void play(t_field *field);
int getcyclesforcop(t_process *now);
void executer(t_field *field, t_process *process);
void mainexecuter(t_field *field, t_process *process);
int istypecorrectnoargreg(t_field *field, t_process *process);
int skipnoarg(t_process *process);
void printplayers(t_field *field);
void simpleresult(t_field *field);
void destroy_field (t_field **field);
int exiter(t_field *field, char *strtoprint);
int	map_to_int(t_field *field, int pos, int size);
void live(t_field *field, t_process *process);
void zjmp(t_field *field, t_process *process);
void and(t_field *field, t_process *process);
/*ядро валидации*/
#endif
