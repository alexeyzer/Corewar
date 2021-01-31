# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/31 14:40:35 by aguiller          #+#    #+#              #
#    Updated: 2021/01/31 20:47:47 by alexzudin        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_VM = valid.c champ_parse.c valider.c placer.c func.c proccore.c check.c \
		check_p2.c procgo.c exec.c mainexecuter.c gamesult.c obliterator.c \
		commands_p1.c commands_p2.c commands_p3.c correct.c visual_core.c\
		visual_utils.c

SRC_DIR_VM = src/vm/

COREWAR_H =	-I includes/
PRINTF_H =	-I libftprintf/includes
LIB_H =	-I libftprintf/libft/


SRCS_VM= $(addprefix $(SRC_DIR_VM), $(SRC_VM))

NAME = corewar

OBJ_VM = $(SRCS_VM:%.c=%.o)

INCNAME1 = includes/vm.h
INCNAME2 = includes/op.h

all: $(NAME)

$(NAME): $(OBJ_VM) 
	@cd libftprintf && $(MAKE) all
	@cp libftprintf/libftprintf.a ./
	@gcc -Wall -Wextra -Werror -ggdb -o $(NAME) $(OBJ_VM) libftprintf.a -lncurses


%.o:%.c $(INCNAME1) $(INCNAME2)
	@gcc -Wall -Wextra -ggdb -Werror $(COREWAR_H) $(PRINTF_H) $(LIB_H) -c $< -o $@

clean:
	@cd libftprintf && $(MAKE) clean	
	@/bin/rm -f $(OBJ_VM)
	@/bin/rm -f libftprintf.a

fclean: clean
	@cd libftprintf && $(MAKE) fclean
	@/bin/rm -f $(NAME)

re: fclean  all 

