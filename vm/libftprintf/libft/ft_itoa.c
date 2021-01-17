/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:22:54 by alexzudin         #+#    #+#             */
/*   Updated: 2020/06/15 10:50:18 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		to_count(long n)
{
	int count;

	count = 0;
	if (n < 0)
	{
		n = n * -1;
		count++;
	}
	if (n == 0)
		count++;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(long int n)
{
	char	*strmem;
	int		i;
	long	nr;

	nr = (long)n;
	strmem = (char*)malloc(sizeof(char) * (to_count(nr) + 1));
	if (strmem == NULL)
		return (NULL);
	strmem[to_count(n)] = '\0';
	i = to_count(nr) - 1;
	if (nr == 0)
		strmem[0] = '0';
	if (n <= -1)
	{
		nr = nr * -1;
		strmem[0] = '-';
	}
	while (nr > 0)
	{
		strmem[i] = ('0' + (nr % 10));
		nr = nr / 10;
		i--;
	}
	return (strmem);
}
