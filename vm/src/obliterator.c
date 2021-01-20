/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obliterator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgonzo <cgonzo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:48:00 by cgonzo            #+#    #+#             */
/*   Updated: 2021/01/20 15:23:32 by cgonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
void destroy_champ_list()
{

}


void destroy_proc_list(t_process *head)
{
    
}

void destroy_field (t_field **field)
{
    t_field *feld;

    feld = &field;
    destroy_proc_list(feld->first);
    destroy_champ_list(feld->champlist);
    free(&field);
    free(feld);
}