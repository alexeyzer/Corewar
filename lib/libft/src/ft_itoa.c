/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 11:02:10 by kjamar            #+#    #+#             */
/*   Updated: 2019/09/21 11:02:15 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		leng(int n, int minus)
{
	int numlen;

	numlen = 1;
	while ((n /= 10))
		numlen++;
	return (numlen + minus);
}

char			*ft_itoa(int n)
{
	char	*num;
	int		minus;
	int		dig;
	int		len;

	dig = 0;
	minus = ((n < 0) ? 1 : 0);
	len = leng(n, minus);
	if ((num = ft_strnew(len)))
	{
		num[len--] = '\0';
		while (len >= minus)
		{
			dig = n % 10;
			if (n < 0)
				num[len--] = (dig * (-1)) + '0';
			else
				num[len--] = dig + '0';
			n /= 10;
		}
		if (minus)
			num[0] = '-';
	}
	return (num);
}
