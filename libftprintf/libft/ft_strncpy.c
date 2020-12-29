/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:10:54 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/20 13:19:39 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int		i;

	i = 0;
	if (!src)
		dst[i] = src[i];
	while (src[i] != '\0' && (len > 0))
	{
		dst[i] = src[i];
		i++;
		len--;
	}
	while (len > 0)
	{
		dst[i] = '\0';
		len--;
		i++;
	}
	return (dst);
}
