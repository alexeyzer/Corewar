/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:54:27 by kjamar            #+#    #+#             */
/*   Updated: 2019/09/21 14:54:33 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = NULL;
	if (s && f && (temp = ft_strnew(ft_strlen(s))))
	{
		while (s[i])
		{
			temp[i] = f(i, s[i]);
			i++;
		}
		temp[i] = '\0';
	}
	return (temp);
}
