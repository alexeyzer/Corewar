/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:10:54 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/20 12:00:42 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int	j;
	int speclen;

	j = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[j] != '\0')
	{
		i = 0;
		if (needle[i] == haystack[j])
		{
			speclen = j;
			while (needle[i] == haystack[j])
			{
				if (needle[i + 1] == '\0')
					return ((char*)&haystack[speclen]);
				i++;
				j++;
			}
			j = speclen;
		}
		j++;
	}
	return (NULL);
}
