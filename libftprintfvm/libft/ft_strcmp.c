/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 20:09:49 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/22 13:14:24 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (((unsigned char)(s1[i])) - ((unsigned char)s2[i]));
		if (s1[i] < s2[i])
			return (((unsigned char)(s1[i])) - ((unsigned char)s2[i]));
		i++;
	}
	return (0);
}
