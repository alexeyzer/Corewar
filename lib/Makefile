# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguiller <aguiller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/21 10:18:18 by kjamar            #+#    #+#              #
#    Updated: 2021/02/01 16:41:27 by aguiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a
CC 				= gcc
FLAG 			= -Wall -Werror -Wextra

DIR_PRINTF 		= ./ft_printf/src/
DIR_LIBFT 		= ./libft/src/
DIR_GNL 		= ./get_next_line/
DIR_O 			= ./obj/

HEADER_PRINTF 	= -I ./ft_printf/
HEADER_LIBFT 	= -I ./libft/
HEADER_GNL 		= -I ./get_next_line/

SOURCES_LIBFT	= ft_memset.c\
					ft_bzero.c\
					ft_memcpy.c\
					ft_memccpy.c\
					ft_memmove.c\
					ft_memchr.c\
					ft_memcmp.c\
					ft_strlen.c\
					ft_strdup.c\
					ft_strcpy.c\
					ft_strncpy.c\
					ft_strcat.c\
					ft_strncat.c\
					ft_strlcat.c\
					ft_strchr.c\
					ft_strrchr.c\
					ft_strstr.c\
					ft_strnstr.c\
					ft_strcmp.c\
					ft_strncmp.c\
					ft_atoi.c\
					ft_isalpha.c\
					ft_isdigit.c\
					ft_isalnum.c\
					ft_isascii.c\
					ft_isprint.c\
					ft_toupper.c\
					ft_tolower.c\
					ft_memalloc.c\
					ft_memdel.c\
					ft_strnew.c\
					ft_strdel.c\
					ft_strclr.c\
					ft_striter.c\
					ft_striteri.c\
					ft_strmap.c\
					ft_strmapi.c\
					ft_strequ.c\
					ft_strnequ.c\
					ft_strsub.c\
					ft_strjoin.c\
					ft_strtrim.c\
					ft_strsplit.c\
					ft_itoa.c\
					ft_putchar.c\
					ft_putstr.c\
					ft_putendl.c\
					ft_putnbr.c\
					ft_putchar_fd.c\
					ft_putstr_fd.c\
					ft_putendl_fd.c\
					ft_putnbr_fd.c\
					ft_lstnew.c\
					ft_lstdelone.c\
					ft_lstdel.c\
					ft_lstadd.c\
					ft_lstiter.c\
					ft_lstmap.c\
					ft_putstr_color.c\
					ft_putnbr_color.c\
					ft_nbrmax.c\
					ft_nbrmin.c\
					ft_abs.c\
					ft_pointertoch.c\
					ft_word_count.c\
					ft_putstr_err.c\
					ft_putstr_err_color.c
SOURCES_PRINTF 	= ft_printf.c\
					handler_f.c\
					option_handle.c\
					option_handle_f2.c\
					parser_fl_type.c\
					write_func.c\
					handler_cspdu.c\
					handler_oxperc.c\
					option_handle_f.c\
					option_handle_f3.c\
					parser_wd_pre_len.c\
					write_func2.c
SOURCES_GNL 	= get_next_line.c

PATH_PRINTF = $(addprefix $(DIR_PRINTF), $(SOURCES_PRINTF))
PATH_LIBFT = $(addprefix $(DIR_LIBFT), $(SOURCES_LIBFT))
PATH_GNL = $(addprefix $(DIR_GNL), $(SOURCES_GNL))

OBJS = $(addprefix $(DIR_O),$(SOURCES_PRINTF:.c=.o)) $(addprefix $(DIR_O),\
$(SOURCES_LIBFT:.c=.o)) $(addprefix $(DIR_O),$(SOURCES_GNL:.c=.o)) 

all: obj $(NAME)
obj:
	@mkdir -p $(DIR_O)
	@$(CC) $(FLAG) $(HEADER_PRINTF) $(HEADER_LIBFT) $(HEADER_GNL) $(PATH_GNL) $(PATH_LIBFT) $(PATH_PRINTF) -c $<
	@mv *.o $(DIR_O)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
clean:
	@rm -rf $(DIR_O)
fclean: clean
	@rm -f $(NAME)
re: clean all
