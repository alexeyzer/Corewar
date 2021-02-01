/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:05:51 by kjamar            #+#    #+#             */
/*   Updated: 2019/09/21 15:05:56 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*temp;
	size_t	needle_len;
	size_t	j;
	size_t	i;

	temp = (char *)haystack;
	if (!(needle_len = ft_strlen(needle)))
		return (temp);
	if (ft_strlen(haystack) < needle_len || len < needle_len)
		return (NULL);
	i = 0;
	while (temp[i] && i <= len - needle_len)
	{
		j = 0;
		while (needle[j] && needle[j] == temp[i + j])
			j++;
		if (j == needle_len)
			return (&temp[i]);
		i++;
	}
	return (NULL);
}
