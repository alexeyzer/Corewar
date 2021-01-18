/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:46:20 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/17 19:57:39 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


t_field     *validation_and_reading(int argc, char **argv)
{
    int         i;
    t_field     *field;
    int         counter;

    i = 1;
    field = (t_field*)malloc(sizeof(t_field));
    counter = 0;
    while (i < argc)
    {
        if (1)
        {
            champ_parse(argv[i], field, counter);
            counter++;
        }
        i++;
    }
    if (counter < MAX_PLAYERS)
        return (field);
    return (field);
}

int main(int argc, char **argv)
{
    t_field *field;
    field   = validation_and_reading(argc, argv);
    return (0);
}