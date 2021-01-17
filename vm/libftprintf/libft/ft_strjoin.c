/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:00:23 by aguiller          #+#    #+#             */
/*   Updated: 2019/10/22 09:31:27 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*memstr;

	if ((s1 == NULL || s2 == NULL))
		return (NULL);
	i = 0;
	j = 0;
	memstr = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (memstr == NULL)
		return (NULL);
	ft_strclr(memstr);
	while (s1[i] != '\0')
	{
		memstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		memstr[i] = s2[j];
		i++;
		j++;
	}
	memstr[i] = '\0';
	return (memstr);
}
