/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:24:48 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/21 23:07:35 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*memstr;
	size_t	i;

	memstr = NULL;
	i = 0;
	if (size >= SIZE_MAX)
		return (NULL);
	memstr = (char*)malloc(size + 1);
	if (memstr == NULL)
		return (NULL);
	while (i < size + 1)
	{
		memstr[i++] = '\0';
	}
	return (memstr);
}
