/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 11:19:11 by kjamar            #+#    #+#             */
/*   Updated: 2019/09/21 11:19:17 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*test_s;

	i = 0;
	test_s = (unsigned char *)s;
	while (i < n)
	{
		if (test_s[i] == (unsigned char)c)
			return (test_s + i);
		i++;
	}
	return (0);
}
