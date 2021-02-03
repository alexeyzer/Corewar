/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:48:37 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/20 11:39:52 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	first;
	size_t	spec;
	char	*memstr;

	i = 0;
	first = 0;
	if (s == NULL)
		return (NULL);
	spec = ft_strlen(s);
	while (s[first] == ' ' || s[first] == '\t' || s[first] == '\n')
		first++;
	while (first < spec && (s[spec - 1] == ' ' || s[spec - 1] == '\t'
				|| s[spec - 1] == '\n'))
		spec--;
	if (spec == first)
		return (ft_strnew(1));
	memstr = ft_strnew(spec - first);
	if (memstr == NULL)
		return (NULL);
	while (first < spec)
		memstr[i++] = s[first++];
	return (memstr);
}
