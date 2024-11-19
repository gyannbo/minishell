# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msloot <msloot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 19:19:04 by msloot            #+#    #+#              #
#    Updated: 2024/11/05 11:19:27 by msloot           ###   ########.fr        #
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

MAKEFLAGS += --silent

SHELL := bash

B =		$(shell tput bold)
BLA =	$(shell tput setaf 0)
RED =	$(shell tput setaf 1)
GRE =	$(shell tput setaf 2)
YEL =	$(shell tput setaf 3)
BLU =	$(shell tput setaf 4)
MAG =	$(shell tput setaf 5)
CYA =	$(shell tput setaf 6)
WHI =	$(shell tput setaf 7)
D =		$(shell tput sgr0)
BEL =	$(shell tput bel)
CLR =	$(shell tput el 1)

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
			

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

# *************************************************************************** #

define	progress_bar
	i=0
	while [[ $$i -le $(words $(SRC_NAME) m m) ]] ; do \
		printf " " ; \
		((i = i + 1)) ; \
	done
	printf "$(B)]\r[$(GRE)"
endef

# *************************************************************************** #
#	RULES	#

all:		launch $(NAME)

launch:
	$(call progress_bar)

$(NAME):	$(OBJ) $(LIBNAME)
	$(CC) $(CFLAGS) $(OBJ) $(LIBNAME) -o $(NAME) $(LIBREADLINE) 
	@printf "\n$(B)$(MAG)$(NAME) compiled$(D)\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@) # 2> /dev/null || true
	$(CC) $(CFLAGS) $(LIBINC) -I$(INC) -c $< -o $@
	@printf "█"

$(LIBNAME):
	@$(MAKE) -C $(LIBPATH)

clean:
	@$(RM) $(OBJ_PATH)
	@$(MAKE) clean -C $(LIBPATH)
	@echo "$(B)cleared$(D)"

fclean:		clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBPATH)

re:			fclean all 

valgrind:
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --log-file=log ./minishell


.PHONY: all clean fclean re valgrind


# **************************************************************************** #
