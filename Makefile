# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/31 14:40:35 by aguiller          #+#    #+#              #
#    Updated: 2021/02/03 16:34:51 by aguiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m

SRC_VM = valid.c champ_parse.c valider.c placer.c func.c proccore.c check.c \
		check_p2.c procgo.c exec.c mainexecuter.c gamesult.c obliterator.c \
		commands_p1.c commands_p2.c commands_p3.c correct.c visual_core.c\
		visual_utils.c

SRC_ASM = main.c validations.c validations_p2.c getline.c commandvalider.c \
		isitcommand.c label.c commandinit.c size.c exit.c \
		argumentvalidations.c  write.c write_utuils.c

SRC_DIR_VM = src/vm/
SRC_DIR_ASM = src/asm/

COREWAR_H =	-I includes/
PRINTFVM_H = -I libftprintf/includes
LIBVM_H =	-I libftprintf/libft/

LIBFT = ./libftprintf/libftprintf.a


SRCS_VM= $(addprefix $(SRC_DIR_VM), $(SRC_VM))

SRCS_ASM = $(addprefix $(SRC_DIR_ASM), $(SRC_ASM))

NAME_VM = corewar

NAME_ASM = asm

INCNAME1 = includes/vm.h
INCNAME2 = includes/op.h
INCNAME3 = includes/corewar.h


OBJ_VM = $(SRCS_VM:%.c=%.o)

OBJ_ASM = $(SRCS_ASM:%.c=%.o)

%.o:%.c
	@gcc -Wall -Wextra -ggdb -Werror $(COREWAR_H) $(PRINTFVM_H) $(LIBVM_H) -c $< -o $@


all: $(NAME_ASM) $(NAME_VM)

$(NAME_VM): $(OBJ_VM) $(LIBFT) $(INCNAME1) $(INCNAME2)
	@gcc -Wall -Wextra -Werror -ggdb -o $(NAME_VM) $(OBJ_VM) ./libftprintf/libftprintf.a -lncurses
	@echo "$(GREEN)VM are created"

$(NAME_ASM): $(OBJ_ASM) $(LIBFT) $(INCNAME2) $(INCNAME3)
	@gcc -Wall -Wextra -Werror -ggdb -o $(NAME_ASM) $(OBJ_ASM) ./libftprintf/libftprintf.a
	@echo "$(GREEN)ASM are created"

$(LIBFT):
	@make -C ./libftprintf

clean:
	@cd libftprintf && $(MAKE) clean
	@/bin/rm -f $(OBJ_VM)
	@/bin/rm -f $(OBJ_ASM)
	@/bin/rm -f libftprintf.a
	@make -C ./libftprintf clean

fclean: clean
	@make -C ./libftprintf fclean
	@/bin/rm -f $(NAME_VM)
	@/bin/rm -f $(NAME_ASM)

re: fclean  all 

