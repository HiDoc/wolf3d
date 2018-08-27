# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaille <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 00:22:44 by abaille           #+#    #+#              #
#    Updated: 2018/07/21 19:01:06 by abaille          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft
MLX = ./minilibx
FRK = -framework
OPEN = OpenGL
APPK = AppKit

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/ \
			./minilibx/ \
			./libft/	\
			/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/

SRC_NAME =	main.c	\
			hook.c	\
			checkerrors.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(FRK) $(OPEN) $(FRK) $(APPK) -o $(NAME) \
	-L$(LIBFT) -lft -L$(MLX) -lmlx 

$(OBJ) : | $(OBJ_PATH)

$(OBJ_PATH) :
		@mkdir objs

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	make -C $(LIBFT) clean
	make -C $(MLX) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
