/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 11:07:09 by kjamar            #+#    #+#             */
/*   Updated: 2019/09/21 11:07:16 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_lstdel(t_list **list, void (*del)(void *, size_t))
{
	if ((*list)->next)
		ft_lstdel(&(*list)->next, del);
	ft_lstdelone(&(*list), del);
}
