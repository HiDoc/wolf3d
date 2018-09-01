# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaille <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 00:22:44 by abaille           #+#    #+#              #
#    Updated: 2018/09/01 15:51:55 by fmadura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= wolf3d
CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror -g
LIBFT 		= ./libft
MLX 		= ./minilibx
FRK			= -framework
OPEN 		= OpenGL
APPK 		= AppKit

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

SRC_PATH 	= ./srcs/
OBJ_PATH 	= ./objs/
INC_PATH 	= ./includes/ \
			  ./minilibx/ \
			  ./libft/includes/	\
			  /System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/

SRC_NAME 	= main.c \
			  hook.c \
			  raycasting.c \
			  thread.c \
			  checkerrors.c \
			  parser.c \
			  img.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	@printf "\nSources are ready to be used !\n"
	@make -C $(LIBFT)
	@make -C $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(FRK) $(OPEN) $(FRK) $(APPK) -o $(NAME) \
	-L$(LIBFT) -lft -L$(MLX) -lmlx 

$(OBJ) : | $(OBJ_PATH)

$(OBJ_PATH) :
	@mkdir objs

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "\rCompiling $< into object file.. $(WAIT)          "
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@printf "\rCompiling $< into object file.. $(OK)            "

clean:
	@make -C $(LIBFT) clean
	@make -C $(MLX) clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)

run: all
	clear
	./Wolf3d

re: fclean all
