/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:03:48 by kjamar            #+#    #+#             */
/*   Updated: 2019/09/21 15:03:55 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	int		i;

	i = size;
	if (size >= (size_t)(-1) || (size + 1) >= (size_t)(-1))
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	str[i] = '\0';
	while (i-- > 0)
		str[i] = '\0';
	return (str);
}
