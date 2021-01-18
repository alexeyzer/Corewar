/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:46:20 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/18 13:05:44 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int  is_key(char *curr, char *next)
{
    if(!next)
        return (0);
    if(ft_atoi(next)&& ft_strequ(curr,"-d")) 
        return(ft_atoi(next));
    return (0);
}
/*является ли ключом, в идеале пусть возвращает значение */
static int  is_champ(char *filename)
{
    if (!ft_strcmp(ft_strsub(filename,ft_strlen(filename) - 4, 4), ".cor"))
    {
        return (1);
    }
    return (0);
}
/*соотвествует ли имя файла(первичное тестирование пройдено)*/

/*парсинг чемпиона*/
t_field     *validation_and_reading(int argc, char **argv)
{
    int     i;
    t_field *field;
    int     counter;

    i = 1;
    counter = 0;
    field =  malloc(sizeof(t_field));
    while (i < argc)
    {
        if (is_champ(argv[i]))
        {
            champ_parse(argv[i], field, counter);
            counter++;
        }
        {
            if(i != argc - 2)
                field->dump = is_key(argv[i],argv[i+1]);
        }
        i++;
    }
    if (counter < MAX_PLAYERS)
        return (NULL);
    field->counter = counter;
    return (field);
}

int main(int argc, char **argv)
{
    t_field *fild;
    
    fild = validation_and_reading(argc, argv);

}