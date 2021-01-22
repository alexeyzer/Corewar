/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obliterator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:48:00 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/22 11:35:18 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
void destroy_champ_list()
{

}

void destroy_field (t_field **field)
{
    t_field *feld;

    feld = &field;
    deleteallproc(feld);
    destroy_champ_list(feld->champlist);
    free(&field);
    free(feld);
}