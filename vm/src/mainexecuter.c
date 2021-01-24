/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainexecuter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:31:11 by aguiller          #+#    #+#             */
/*   Updated: 2021/01/24 16:44:35 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void mainexecuter(t_field *field, t_process *process)
{
    if (process->cop == 0)
        live(field, process);
    if(process->cop == 8)
        zjmp(field, process);
}