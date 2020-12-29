/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:10:54 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/20 12:16:54 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*curent_head;

	i = 0;
	curent_head = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			curent_head = &s[i];
		i++;
	}
	if (s[i] == (char)c)
		curent_head = &s[i];
	return ((char*)curent_head);
}
