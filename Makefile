# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msloot <msloot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 19:19:04 by msloot            #+#    #+#              #
#    Updated: 2024/12/16 22:12:12 by gbonis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell
CC = 	cc
RM = 	rm -rf

CFLAGS =	-Wall -Werror -Wextra
CFLAGS +=	-g
# CFLAGS +=	-fsanitize=address

# **************************************************************************** #
#	MAKEFILE	#

SHELL := bash

# **************************************************************************** #
#   LIB     #

LIBPATH =   ./libft/
LIBNAME =   $(LIBPATH)libft.a
LIBINC =    -I$(LIBPATH)

# **************************************************************************** #
#   READLINE     #

LIBREADLINE = -lreadline

# **************************************************************************** #
#	SOURCE	#

SRC_PATH =	./src/
OBJ_PATH =	./obj/
INC =		./inc/

SRC_NAME =	main.c \
			parse.c \
			handle_cmd_str.c \
			signals.c \
			get_path.c \
			utils/get_path_utils.c \
			path_splitting.c \
			exec.c \
			check_match.c \
			redir_pipes.c \
			utils/redir_pipes_utils.c \
			expand.c \
			utils/expand_utils.c \
			do_put_in_string.c \
			quotes.c \
			quote_parsing.c \
			manage_q_tok.c \
			utils/manage_q_tok_utils.c \
			manage_rest_tok.c \
			manage_count.c\
			type_func_problem.c\
			builtin/exec.c \
			builtin/echo.c \
			builtin/cd.c \
			builtin/env.c \
			builtin/pwd.c \
			utils/error.c \
			norm_get_right_pos.c\
			norm_get_right_pos_second.c\
			norm_manage_rest_tok.c\
			norm_has_type.c\
			norm_manage_q_tok_utils.c\
			norm_manage_q_tok_utils_second.c\
			quote_expand.c\
			norm_quote_expand.c\
			do_quote_expand.c\
#			tokenise_redpip.c\
#			redpip_tab_utils.c\
#			redpip_tab_utils2.c\
#			string_allocation_redpip.c\

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))


all:	 $(NAME)

$(NAME):	$(OBJ) $(LIBNAME)
	$(CC) $(CFLAGS) $(OBJ) $(LIBNAME) -o $(NAME) $(LIBREADLINE) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(dir $@) # 2> /dev/null || true
	$(CC) $(CFLAGS) $(LIBINC) -I$(INC) -c $< -o $@

$(LIBNAME):
	$(MAKE) -C $(LIBPATH)

clean:
	$(RM) $(OBJ_PATH)
	$(MAKE) clean -C $(LIBPATH)

fclean:		clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBPATH)

re:			fclean all 

valgrind:
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --log-file=log ./minishell


.PHONY: all clean fclean re valgrind


# **************************************************************************** #
