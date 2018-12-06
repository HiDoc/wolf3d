# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaille <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 00:22:44 by abaille           #+#    #+#              #
#    Updated: 2018/11/27 14:42:22 by fmadura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= wolf3d
CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror -g
LIBFT 		= ./libft

#color
YELLOW		= "\\033[33m"
BLUE		= "\\033[34m"
RED			= "\\033[31m"
WHITE		= "\\033[0m"
CYAN		= "\\033[36m"
GREEN		= "\\033[32m"
BOLD		= "\\033[1m"
PINK		= "\\033[95m"

OK		= $(CYAN)OK$(WHITE)
WAIT		= $(RED)WAIT$(WHITE)

ID_UN 		= $(shell id -un)
SRC_PATH 	= ./srcs/
OBJ_PATH 	= ./objs/
INC_PATH	= ./includes/ \
			  ./libft/includes/ 

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	CC = clang -std=c99
	INC_PATH 	+= /usr/include/SDL2/ 

OPEN 		= -L/usr/lib/x86_64-linux-gnu -lm -lpthread 
else
	INC_PATH 	+= /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.8/include/ \
				   /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.8/include/SDL2/ \
				   /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.14/include/ \
				   /Users/$(ID_UN)/.brew/Cellar/sdl2_image/2.0.3/include/ \
				   /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.2_3/include/ \
				   -F -framework Cocoa 

FRK		= -framework
OPEN 		= OpenGL
APPK 		= AppKit
endif

SRC_NAME 	= main.c \
			  sdl_hook.c \
			  raycasting.c \
			  thread.c \
			  checkerrors.c \
			  parser.c \
			  ui.c \
			  portal.c \
			  struct_line.c \
			  struct_sdl.c \
			  struct_env.c \
			  struct_obj.c \
			  utils_tab.c \
			  utils_sdl.c \
			  utils_maths.c \
			  utils_point.c \
			  utils_textures.c \
			  struct_img.c \
			  musics.c		\
			  sdl_mouse.c	\
			  objects_walls.c \
			  weapons.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LSDL2 	 = -L/Users/$(ID_UN)/.brew/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

.PHONY: all re clean fclean
.SILENT:
all: $(NAME)

$(NAME): $(OBJ)
	@printf "\nSources are ready to be used !\n"
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(FRK) $(OPEN) $(FRK) $(APPK) -o $(NAME) \
		-L$(LIBFT) -lft \
		$(INC) $(LSDL2)

$(OBJ) : | $(OBJ_PATH)

$(OBJ_PATH) :
	@mkdir objs

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "\rCompiling $< into object file.. $(WAIT)          "
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@printf "\rCompiling $< into object file.. $(OK)            "

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(OBJ_PATH)
	@rm -rf $(NAME).dSYM/

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)

run: all
	clear
	./wolf3d

lldb:
	gcc ./srcs/*.c $(INC) $(CFLAGS) $(LIB) $(LSDL2) $(FRK) $(OPEN) $(FRK) $(APPK) -o $(NAME) \
		-L$(LIBFT) -lft
	lldb ./wolf3d

fsani:
	gcc ./srcs/*.c $(INC) $(CFLAGS) -fsanitize=address \
		$(LIB) $(LSDL2) $(FRK) $(OPEN) $(FRK) $(APPK) -o $(NAME) \
		-L$(LIBFT) -lft
	./wolf3d

valg:
	gcc ./srcs/*.c $(INC) $(CFLAGS) \
	$(LIB) $(LSDL2) $(FRK) $(OPEN) $(FRK) $(APPK) -o $(NAME) \
	-L$(LIBFT) -lft
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=definite ./wolf3d

re: fclean all
