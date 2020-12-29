/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:13:08 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/20 12:56:48 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	char		*a;
	const char	*b;

	a = (char*)destination;
	b = (char*)source;
	while (n-- > 0)
	{
		if (*b == (char)c)
		{
			*a = *b;
			return (a + 1);
		}
		*a = *b;
		a++;
		b++;
	}
	return (NULL);
}
