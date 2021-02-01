/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:53:38 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/20 14:26:00 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int i;

	i = 0;
	if (s == NULL)
		return ;
	if (f == NULL)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
