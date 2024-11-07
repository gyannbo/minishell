# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msloot <msloot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/21 17:15:16 by msloot            #+#    #+#              #
#    Updated: 2024/06/19 22:05:30 by msloot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a
CC = 	cc
AR =	ar rcs
RM = 	rm -rf

CFLAGS =	-Wall -Werror -Wextra
# CFLAGS +=	-g
# CFLAGS +=	-fsanitize=address
# CFLAGS +=	-Wsuggest-attribute=const

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

# **************************************************************************** #
#	SOURCE		#

SRC_PATH =			./src/
OBJ_PATH =			./obj/
INC =				./inc/

SRC_NAME = \
	ft_is/ft_isalpha.c ft_is/ft_isdigit.c ft_is/ft_isalnum.c \
	ft_is/ft_isascii.c ft_is/ft_isprint.c ft_is/ft_isspace.c \
	ft_is/ft_isupper.c ft_is/ft_islower.c \
	ft_is/ft_is_in.c  ft_is/ft_is_all.c ft_is/ft_is_any.c \
	str/ft_strlen.c str/ft_strchr.c str/ft_strrchr.c str/ft_strcmp.c str/ft_strncmp.c str/ft_strcpy.c str/ft_strlcpy.c \
	str/ft_strcat.c str/ft_strlcat.c str/ft_strnstr.c \
	str/ft_toupper.c str/ft_tolower.c \
	nbr/ft_abs.c nbr/ft_min.c nbr/ft_max.c \
	nbr/ft_nbrlen.c nbr/ft_nbrlen_base.c \
	nbr/ft_unbrlen.c nbr/ft_unbrlen_base.c \
	mem/ft_bzero.c mem/ft_memset.c mem/ft_memcpy.c mem/ft_memcmp.c mem/ft_memchr.c mem/ft_memmove.c \
	mem/ft_free_2d.c mem/ft_2d_size.c \
	convert/ft_atoi.c convert/ft_aton.c convert/ft_atoun.c convert/ft_atoi_digits_only.c  convert/ft_itoa.c \
	convert/ft_ntoa_base.c convert/ft_ntoa.c \
	convert/ft_untoa_base.c convert/ft_untoa.c \
	convert/ft_nbr_convert_base.c convert/ft_nbr_convert.c \
	convert/ft_unbr_convert_base.c convert/ft_unbr_convert.c \
	convert/ft_check_base.c \
	str/ft_strdup.c str/ft_strndup.c mem/ft_calloc.c \
	str/ft_strjoin.c str/ft_strjoin_free.c str/ft_substr.c str/ft_strtrim.c \
	str/ft_split.c str/ft_split_any_of.c str/ft_split_whitespace.c \
	put/ft_putchar_fd.c put/ft_putchar.c put/ft_putstr_fd.c put/ft_putstr.c put/ft_putendl_fd.c put/ft_puterr.c \
	put/ft_putnbr_base_fd.c put/ft_putnbr_base.c \
	put/ft_putnbr_fd.c put/ft_putnbr.c \
	put/ft_putunbr_base_fd.c put/ft_putunbr_base.c \
	put/ft_putunbr_fd.c put/ft_putunbr.c \
	str/ft_striteri.c str/ft_strmapi.c \
	lst/ft_lstsize.c lst/ft_lstlast.c lst/ft_lstnew.c lst/ft_lstadd_front.c lst/ft_lstadd_back.c lst/ft_lstiter.c \
	lst/ft_lstdelone.c lst/ft_lstclear.c lst/ft_lstmap.c \
	read/get_next_line.c read/count_line.c \

SRC =				$(addprefix $(SRC_PATH), $(SRC_NAME))
# SRC =				$(wildcard $(SRC_PATH)*.c) $(wildcard $(SRC_PATH)**/*.c)
#SRC_NAME =			$(subst $(SRC_PATH), , $(SRC))

OBJ_NAME =			$(SRC_NAME:.c=.o)
OBJ =				$(addprefix $(OBJ_PATH), $(OBJ_NAME))

# *************************************************************************** #

define	progress_bar
	@i=0
	@while [[ $$i -le $(words $(SRC)) ]] ; do \
		printf " " ; \
		((i = i + 1)) ; \
	done
	@printf "$(B)]\r[$(D)"
endef

# *************************************************************************** #
#	RULES		#

all:		launch $(NAME)
	@printf "\n$(B)$(MAG)$(NAME) compiled$(D)\n"

launch:
	$(call progress_bar)

$(NAME):	$(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
	@printf "$(B)$(GRE)█$(D)"

clean:
	@$(RM) $(OBJ_PATH)

fclean:		clean
	@$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re launch

# **************************************************************************** #
