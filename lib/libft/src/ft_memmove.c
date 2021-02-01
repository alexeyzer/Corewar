/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 11:35:18 by kjamar            #+#    #+#             */
/*   Updated: 2019/09/21 11:35:25 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = 0;
	if (len == 0)
		return (dst);
	if (src > dst)
		ft_memcpy(dst, src, len);
	else if (src < dst)
		while (++i <= len)
			((char*)dst)[len - i] = ((char *)src)[len - i];
	return (dst);
}
