/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgonzo <cgonzo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:45:16 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/19 17:56:27 by cgonzo           ###   ########.fr       */
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

typedef struct	s_process
{
    int pos;
    int idle;
    int carry;
    char color;
    //int hp;
    //t_champ *host;
    int reg[REG_NUMBER];
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
    t_process *first_proc;
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
    int sorted;
    struct	s_champlist *next;
}               t_champlist;
typedef struct	s_field
{
    int counter;
    int dump;
    int cycle;
    t_champlist *champlist;
    t_champlist *now;
    t_cell mass[MEM_SIZE];
}				t_field;
/*counter - количество чемпионов
 dump - когда выгрузить состояние поля, если "-1", то выгружать его каждую итерацию
  champ_first - корень списка чемпионов 
  begin_list - начало списка клеток, составляющих поле
   */
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
/*ядро валидации*/
#endif
