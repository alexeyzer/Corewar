/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:37:25 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/20 12:38:21 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*a;
	const char		*b;
	size_t			i;

	i = len;
	a = (char*)dst;
	b = (char*)src;
	if (a == NULL && b == NULL)
		return (NULL);
	if (a > b)
	{
		while (i > 0)
		{
			a[i - 1] = b[i - 1];
			i--;
		}
	}
	if (b > a)
		ft_memcpy(a, b, i);
	return (a);
}
