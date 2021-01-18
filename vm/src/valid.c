/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgonzo <cgonzo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:46:20 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/18 17:28:47 by cgonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int  is_champ(char *filename)
{
    if (!filename)
        exit(-1);
    if(ft_strlen(filename) < 4)
        return (0);
    if (!ft_strcmp(ft_strsub(filename,ft_strlen(filename) - 4, 4), ".cor"))
    {
        return (1);
    }
    return (0);
}
/*соотвествует ли имя файла(первичное тестирование пройдено)*/

static int  is_key_dump(char *curr, char *next, t_field *field)
{
    if(!next || !curr)
        return (MISTAKESYMB);
    if((ft_atoi(next) || ft_strequ(next,"0"))&& ft_strequ(curr,"-dump")) 
    {
        field->dump = ft_atoi(next);
        return (1);
    }
    return (MISTAKESYMB);
}

static int  is_key_n(char *curr, char *next, char *nextnext,  t_field *field)
{
    int number;
    t_champlist *change;

    number = 0;
    if (curr == NULL || next == NULL || nextnext == NULL)
        return(MISTAKESYMB);
    if ((ft_atoi(next) || ft_strequ(next,"0")) && ft_strequ(curr,"-n"))
    {
        if (!(ft_strequ(next,"0")))
            number = ft_atoi(next);
        if (number > 3 || number < 0 || !(is_champ(nextnext)))
            return (MISTAKESYMB);
        if ((change = isitbusy(field->champlist, number)))
        {
            change->place = field->counter;
            change->nowchamp->number = field->counter;
            field->now->place = number;
        }
        else
            field->now->place = number;
        return (1);
    }
    return (-1);
}
/*является ли ключом, в идеале пусть возвращает значение */

/*парсинг чемпиона*/
t_field     *validation_and_reading(int argc, char **argv)
{
    int     i;
    t_field *field;
    //int     miss;
    //char * *input;

    i = 1;
    //input = ft_strsplit(argv,' ');
    field = init();
    while (i < argc)
    {
        if (is_champ(argv[i]))
        {
            champ_parse(argv[i], field);
            (field->counter)++;
        }
        else
        {
            if (is_key_dump(argv[i],argv[i+1], field) != MISTAKESYMB)
                i+=1;
            else
            {
                if(is_key_n(argv[i],argv[i+1], argv[i+ 2], field) == MISTAKESYMB)
                    exit(-1);
                else
                    i+=1;
            }
        }
        i++;
    }
    if (field->counter > MAX_PLAYERS)
        return (NULL);
    return (field);
}

int main(int argc, char **argv)
{
    t_field *fild;
    
    fild = validation_and_reading(argc, argv);
    place(fild);
}