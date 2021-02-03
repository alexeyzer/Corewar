/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 16:24:41 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/22 16:29:40 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddlast(t_list **head, t_list *new)
{
	t_list *list;

	if ((*head) = NULL || new == NULL)
		return (NULL);
	list = *head;
	while (list->next != NULL)
		list = list->next;
	list->next = new;
}
