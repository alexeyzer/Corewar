/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:45:16 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/17 17:08:16 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
#include "op.h"
# include "ft_printf.h"
# include "libft.h"
#include <fcntl.h>
typedef struct	s_process
{
    int pos;
    int idle;
    int carry;
    //int hp;
    //t_champ *host;
    struct	s_process *child;
    struct	s_process *parent;
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
    char meaning;
   // int number;
    char color;
   // t_cell *prev;
   /// t_cell *next;
}				t_cell;
/*meaning - значение в клетке number - номер prev/next -указатели на соседей*/
typedef struct	s_champ
{
   // int idle;
    t_header *inf;
    //int hp;
    int number;
    t_process *first_proc;
    struct	s_champ *next;
}				t_champ;
/*
нейм - имя
коммент - коммент 
first_proc - ссылка на каретку(ки) 
next - следующий чемпион в списке
у игрока есть N регистров для хранения данных */
typedef struct	s_field
{
    int counter;
    int dump;
    int cycle;
    t_champ *champ_first;
    t_cell mass[MEM_SIZE];
}				t_field;
/*counter - количество чемпионов
 dump - когда выгрузить состояние поля, если "-1", то выгружать его каждую итерацию
  champ_first - корень списка чемпионов 
  begin_list - начало списка клеток, составляющих поле
   */
t_field *validation_and_reading(int argc, char *argv[]);
/*ядро валидации*/
#endif
