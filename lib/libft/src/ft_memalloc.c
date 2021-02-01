/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 11:16:03 by kjamar            #+#    #+#             */
/*   Updated: 2019/09/21 11:16:07 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*temp;
	int		i;
	int		n;

	i = 0;
	n = size;
	if (!(temp = (void *)malloc(size)))
		return (NULL);
	while (n > 0)
	{
		((unsigned char *)temp)[i] = 0;
		n--;
		i++;
	}
	return (temp);
}
