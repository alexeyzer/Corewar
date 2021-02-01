# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/31 14:40:35 by aguiller          #+#    #+#              #
#    Updated: 2021/02/01 17:22:58 by aguiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m

SRC_VM = valid.c champ_parse.c valider.c placer.c func.c proccore.c check.c \
		check_p2.c procgo.c exec.c mainexecuter.c gamesult.c obliterator.c \
		commands_p1.c commands_p2.c commands_p3.c correct.c visual_core.c\
		visual_utils.c

SRC_ASM = analysis_utils.c analysis.c arg_math.c argument_checks.c \
			asm.c check_operations.c cleanup.c encoding_utils.c \
			encoding.c error_manager.c filename_util.c init.c \
			print_debug.c special_arg_utils.c special_args.c \
			to_bytecode.c utils.c utils2.c write_exec_code.c \
			write_header.c write_helper.c

SRC_DIR_VM = src/vm/
SRC_DIR_ASM = src/asm/

COREWAR_H =	-I includes/
PRINTFVM_H = -I libftprintfvm/includes
LIBVM_H =	-I libftprintfvm/libft/

LIBASM_H = -I lib/includes/


SRCS_VM= $(addprefix $(SRC_DIR_VM), $(SRC_VM))

SRCS_ASM = $(addprefix $(SRC_DIR_ASM), $(SRC_ASM))

NAME_VM = corewar

NAME_ASM = asm

INCNAME1 = includes/vm.h
INCNAME2 = includes/op.h
INCNAME3 = includes/asm.h
INCNAME4 = includes/errors.h
INCNAME4 = includes/oplist_asmh.h

OBJ_VM = $(SRCS_VM:%.c=%.o)

%.o:%.c 
	@gcc -Wall -Wextra -ggdb -Werror $(COREWAR_H) $(PRINTFVM_H) $(LIBVM_H) $(LIBASM_H) -c $< -o $@

OBJ_ASM = $(SRCS_ASM:%.c=%.o)

all: $(NAME_VM) $(NAME_ASM)

$(NAME_VM): $(OBJ_VM)  $(INCNAME1) $(INCNAME2)
	@cd libftprintfvm && $(MAKE) all
	@mv libftprintfvm/libftprintf.a ./libftprintfvm.a
	@gcc -Wall -Wextra -Werror -ggdb -o $(NAME_VM) $(OBJ_VM) libftprintfvm.a -lncurses
	@echo "$(GREEN)VM are created"

$(NAME_ASM): $(OBJ_ASM) 
	@cd lib && $(MAKE) all
	@mv lib/libft.a ./lib.a
	@gcc -Wall -Wextra -Werror -ggdb -o $(NAME_ASM) $(OBJ_ASM) lib.a
	@echo "$(GREEN)ASM are created"

clean:
	@cd libftprintfvm && $(MAKE) clean
	@cd lib && $(MAKE) clean
	@/bin/rm -f $(OBJ_VM)
	@/bin/rm -f $(OBJ_ASM)
	@/bin/rm -f libftprintfvm.a
	@/bin/rm -f lib.a

fclean: clean
	@cd libftprintfvm && $(MAKE) fclean
	@cd lib && $(MAKE) fclean
	@/bin/rm -f $(NAME_VM)
	@/bin/rm -f $(NAME_ASM)

re: fclean  all 

