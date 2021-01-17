/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:27:13 by alexzudin         #+#    #+#             */
/*   Updated: 2021/01/17 16:21:40 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "op.h"

# define COLOR
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PINK		"\033[35m"
# define GRBL		"\033[36m"
# define GREY		"\033[37m"
# define NO			"\033[0m"

typedef struct	s_diretcommand
{
	int					online;
	int					commandnum;
	int                	typeparams[3];
	char				**param;
	double				*paramtransmited;
}				t_diretcommand;

typedef struct	s_command
{
	char                *name;
	int					code;
    int                 countofparams;
	int                	typeparams[3];
	int					argumentcode;
	int					dir_size;
}				t_command;

#endif
