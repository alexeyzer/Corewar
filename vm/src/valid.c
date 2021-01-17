/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:46:20 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/17 16:45:08 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


t_field     *validation_and_reading(int argc, char *argv[])
{
    int     i;
    t_field *field;
    int     counter;

    i = 1;
    counter = 0;
    while (i < argc)
    {
        if (1)
        {
            counter++;
        }
        i++;
    }
    if (counter < MAX_PLAYERS)
        return (field);
    return (field);
}
