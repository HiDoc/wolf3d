# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaille <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 16:35:09 by abaille           #+#    #+#              #
#    Updated: 2019/04/07 19:05:28 by sgalasso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = 

#color
YELLOW		= "\\033[33m"
BLUE		= "\\033[34m"
RED			= "\\033[31m"
WHITE		= "\\033[0m"
CYAN		= "\\033[36m"
GREEN		= "\\033[32m"
BOLD		= "\\033[1m"
PINK		= "\\033[95m"

OK			= $(CYAN)OK$(WHITE)
WAIT		= $(RED)WAIT$(WHITE)

INC_PATH = ./includes/
SRC_PATH = ./srcs/
OBJ_PATH = ./objs/

SRC_NAME =	ft_atoi.c      \
			ft_bzero.c     \
			ft_isalnum.c   \
			ft_isalpha.c   \
			ft_isascii.c   \
			ft_isdigit.c   \
			ft_isprint.c   \
			ft_itoa.c      \
			ft_lstadd.c    \
			ft_lstdel.c    \
			ft_lstdelone.c \
			ft_lstiter.c   \
			ft_lstnew.c    \
			ft_memalloc.c  \
			ft_memccpy.c   \
			ft_memchr.c    \
			ft_memcmp.c    \
			ft_memcpy.c    \
			ft_memdel.c    \
			ft_memmove.c   \
			ft_memset.c    \
			ft_putchar_fd.c \
			ft_putchar.c    \
			ft_putendl_fd.c \
			ft_putendl.c    \
			ft_putnbr_fd.c  \
			ft_putnbr.c     \
			ft_putstr_fd.c  \
			ft_putstr.c     \
			ft_strcat.c     \
			ft_strchr.c     \
			ft_strclr.c     \
			ft_strcmp.c     \
			ft_strcpy.c     \
			ft_strdel.c     \
			ft_strdup.c     \
			ft_strequ.c     \
			ft_striter.c    \
			ft_striteri.c   \
			ft_strjoin.c    \
			ft_strljoin.c    \
			ft_strrjoin.c    \
			ft_strlcat.c    \
			ft_strlen.c     \
			ft_strmap.c     \
			ft_strmapi.c    \
			ft_strncat.c    \
			ft_strncmp.c    \
			ft_strncpy.c    \
			ft_strnequ.c    \
			ft_strnew.c     \
			ft_strnstr.c    \
			ft_strrchr.c    \
			ft_strsplit.c   \
			ft_strstr.c     \
			ft_strsub.c     \
			ft_strtrim.c    \
			ft_tolower.c    \
			ft_toupper.c 	\
			get_next_line.c	\
			ft_ftoa.c		\
			ft_modf.c		\
			ft_abs.c		\
			ft_pow.c		\
			ft_clamp.c		\
			lifetime.c

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@printf "\nLibft.a $(GREEN)compiled !$(WHITE)\n"
	@ranlib $(NAME)

$(OBJ) : | $(OBJ_PATH)

$(OBJ_PATH) :
	@mkdir objs

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "\rCompiling $< into object file.. $(WAIT)          "
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@printf "\rCompiling $< into object file.. $(OK)            "

.PHONY: all clean fclean re

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all
