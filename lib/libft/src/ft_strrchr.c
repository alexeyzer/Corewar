/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:06:42 by kjamar            #+#    #+#             */
/*   Updated: 2019/09/21 15:06:46 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			j = i;
		i++;
	}
	if (s[j] == (char)c)
		return ((char *)s + j);
	if ((char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}
