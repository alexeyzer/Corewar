/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 03:29:54 by aguiller          #+#    #+#             */
/*   Updated: 2020/01/27 14:52:51 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count(char *str)
{
	int r;
	int j;
	int i;

	i = 0;
	r = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			j++;
		else if (j > 0)
		{
			r++;
			j = 0;
		}
		i++;
	}
	if (j > 0)
		r++;
	return (r);
}

char	**maker_massive(char *str)
{
	char	**massive;
	int		i;
	int		j;
	int		r;

	r = 0;
	i = 0;
	j = 0;
	massive = (char**)malloc(sizeof(char*) * (count(str) + 1));
	while (str[r] != '\0')
	{
		if (str[r] != ' ' && str[r] != '\t' && str[r] != '\n' && str[r] != '\0')
			j++;
		else if (j > 0)
		{
			massive[i++] = (char*)malloc(sizeof(char) * (j + 1));
			j = 0;
		}
		r++;
	}
	if (count(str) != 0)
		massive[i] = (char*)malloc(sizeof(char) * (j + 1));
	else
		massive[i] = 0;
	return (massive);
}

void	put(char **massive, char *str)
{
	int i;
	int j;
	int r;

	r = 0;
	j = 0;
	i = 0;
	while (str[r] != '\0')
	{
		if (str[r] != ' ' && str[r] != '\t' && str[r] != '\n')
		{
			massive[i][j] = str[r];
			j++;
		}
		else if (j > 0)
		{
			massive[i][++j] = '\0';
			i++;
			j = 0;
		}
		r++;
	}
	if (j > 0)
		massive[i][j] = '\0';
}

char	**ft_split_whitespaces(char *str)
{
	char	**massive;

	massive = maker_massive(str);
	put(massive, str);
	if (massive[0] != 0)
		massive[count(str)] = 0;
	return (massive);
}
