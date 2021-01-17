/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 15:41:07 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/20 12:22:32 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t len;

	i = 0;
	j = 0;
	len = ft_strlen(src);
	if (!dst && !src)
		return (0);
	while (dst[i] != '\0' && i < size)
		i++;
	while (i + 1 < size && src[j] && size > 0)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (j > 0)
	{
		dst[i] = '\0';
		return (i + len - j);
	}
	return (i + len);
}
