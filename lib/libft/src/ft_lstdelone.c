/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 11:08:35 by kjamar            #+#    #+#             */
/*   Updated: 2019/09/21 11:08:44 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **list, void (*del)(void *, size_t))
{
	del((*list)->content, (*list)->content_size);
	free(*list);
	*list = NULL;
}
