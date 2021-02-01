/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 09:36:37 by kjamar            #+#    #+#             */
/*   Updated: 2020/11/16 09:36:41 by kjamar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_putstr_bold(char *color)
{
	if (!ft_strcmp(color, "bold red"))
		color = "1;31m";
	else if (!ft_strcmp(color, "bold green"))
		color = "1;32m";
	else if (!ft_strcmp(color, "bold yellow"))
		color = "1;33m";
	else if (!ft_strcmp(color, "bold blue"))
		color = "1;34m";
	else if (!ft_strcmp(color, "bold magenta"))
		color = "1;35m";
	else if (!ft_strcmp(color, "bold cyan"))
		color = "1;36m";
	return (color);
}

void			ft_putnbr_color(int nbr, char *color)
{
	ft_putstr("\033[");
	if (!ft_strcmp(color, "black"))
		color = "30m";
	else if (!ft_strcmp(color, "red"))
		color = "0;31m";
	else if (!ft_strcmp(color, "green"))
		color = "0;32m";
	else if (!ft_strcmp(color, "yellow"))
		color = "0;33m";
	else if (!ft_strcmp(color, "blue"))
		color = "0;34m";
	else if (!ft_strcmp(color, "magenta"))
		color = "0;35m";
	else if (!ft_strcmp(color, "cyan"))
		color = "0;36m";
	else
		color = ft_putstr_bold(color);
	ft_putstr(color);
	ft_putnbr(nbr);
	ft_putstr("\033[0m");
}
