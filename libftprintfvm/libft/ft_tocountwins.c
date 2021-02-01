/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tocountwins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 16:56:08 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/22 17:17:57 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tocountwins(char const *s, char c)
{
	int	i;
	int counter;

	i = 0;
	if (!s || !c)
		return (0);
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			counter++;
			while (s[i + 1] != c && s[i + 1] != '\0')
				i++;
		}
		i++;
	}
	return (counter);
}
