/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:46:20 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/24 14:46:40 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int  is_champ(char *filename)
{
    char *filename1;

    filename1 = NULL;
    if (!filename)
        exiter(NULL, "Error with file name ocured");
    if(ft_strlen(filename) < 4)
        return (0);
    filename1 = ft_strsub(filename,ft_strlen(filename) - 4, 4);
    if (!ft_strcmp(filename1, ".cor"))
    {
        if (filename1 != NULL)
            free (filename1);
        return (1);
    }
    if (filename1 != NULL)
        free (filename1);
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
    field->now->nowchamp = createchamp();
    if (curr == NULL || next == NULL || nextnext == NULL)
        return(MISTAKESYMB);
    if ((ft_atoi(next) || ft_strequ(next,"0")) && ft_strequ(curr,"-n"))
    {
        if (!(ft_strequ(next,"0")))
            number = ft_atoi(next);
        if (number > 4 || number < 1 || !(is_champ(nextnext)))
            return (MISTAKESYMB);
        if ((change = isitbusy(field->champlist, number)))
        {
            change->nowchamp->number = getmin(field);
            field->now->nowchamp->number = number;
        }
        else
            field->now->nowchamp->number = number;
        return (1);
    }
    return (MISTAKESYMB);
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
            if (field->now->nowchamp != NULL)
                champ_parse(argv[i], field);
            else
            {
                champ_parse(argv[i], field);
                (field->counter)++;
            }
        }
        else
        {
            if (is_key_dump(argv[i],argv[i+1], field) != MISTAKESYMB)
                i+=1;
            else
            {
                if(is_key_n(argv[i],argv[i+1], argv[i+ 2], field) == MISTAKESYMB)
                    exiter(field, "Error with param parse");
                else
                    i+=1;
            }
        }
        i++;
    }
    if (getcountoflist(field->champlist) > MAX_PLAYERS)
        return (NULL);
    return (field);
}

int main(int argc, char **argv)
{
    t_field *fild;
    
    fild = validation_and_reading(argc, argv);
    currectnum(fild);
    makecolor(fild->champlist);
    place(fild);
    init_proc(fild);
    printplayers(fild);
    play(fild);
    simpleresult(fild);
    //field_print(fild);
    destroy_field(&fild);
}