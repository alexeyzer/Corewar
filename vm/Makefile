# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehell <фпгшддук@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/06 22:26:44 by aguiller          #+#    #+#              #
#    Updated: 2020/10/11 10:23:28 by aguiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = valid.c champ_parse.c valider.c placer.c func.c

SRC_DIR = src/

COREWAR_H =	-I includes/
PRINTF_H =	-I libftprintf/includes
LIB_H =	-I libftprintf/libft/


SRCS=$(addprefix $(SRC_DIR), $(SRC))

NAME = corewar

OBJ = $(SRCS:%.c=%.o)

INCNAME1 = includes/vm.h
INCNAME2 = includes/op.h

all: $(NAME)

$(NAME): $(OBJ) 
	@cd libftprintf && $(MAKE) all
	@cp libftprintf/libftprintf.a ./
	@gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) libftprintf.a


%.o:%.c $(INCNAME1)
	gcc -Wall -Wextra -ggdb -Werror $(COREWAR_H) $(PRINTF_H) $(LIB_H) -c $< -o $@

clean:
	@cd libftprintf && $(MAKE) clean	
	@/bin/rm -f $(OBJ)
	@/bin/rm -f libftprintf.a

fclean: clean
	@cd libftprintf && $(MAKE) fclean
	@/bin/rm -f $(NAME)

re: fclean  all 

