/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:06:19 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/22 17:20:19 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		freez(t_list *lst)
{
	if (lst->next)
		freez(lst);
	free(lst);
}

void			ft_lstdelif(t_list *lst, int (*f)(t_list *elem))
{
	if (lst == NULL || f == NULL)
		return ;
	if (lst->next != NULL)
		ft_lstiter(lst->next, f);
	if ((f(lst)))
	{
		freez(lst);
	}
}
