# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaille <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 00:22:44 by abaille           #+#    #+#              #
#    Updated: 2018/12/27 19:08:53 by sgalasso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= wolf3d
CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror -O3 -g -fsanitize=address
LIBFT 		= ./libft
LEN_NAME	=	`printf "%s" $(NAME) |wc -c`
DELTA		=	$$(echo "$$(tput cols)-32-$(LEN_NAME)"|bc)

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
INC_PATH 	+= /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.9/include/ \
				/Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.9/include/SDL2/ \
				/Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.14/include/ \
				/Users/$(ID_UN)/.brew/Cellar/sdl2_image/2.0.4/include/ \
				/Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.4/include/
endif

SRC_NAME 	= main.c \
			  sdl_hook.c \
			  raycasting.c \
			  thread.c \
			  parser.c \
			  ui.c \
			  struct_line.c \
			  struct_sdl.c \
			  struct_env.c \
			  struct_enemy.c \
			  struct_bots.c \
			  struct_obj.c \
			  struct_minimap.c \
			  utils_tab.c \
			  utils_sdl.c \
			  utils_maths.c \
			  utils_point.c \
			  utils_fog.c \
			  utils_textures.c \
			  utils_tron.c \
			  utils_free.c \
			  utils_ui.c \
			  struct_img.c \
			  musics.c		\
			  sdl_mouse.c	\
			  objects_walls.c \
			  weapons.c

OBJ_NAME	= $(SRC_NAME:.c=.o)
LSDL2		= -L/Users/$(ID_UN)/.brew/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

SRC			= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC			= $(addprefix -I, $(INC_PATH))
DIR			= $(sort $(dir $(OBJ)))
NB			= $(words $(SRC_NAME))
INDEX		= 0

SHELL		:=	bash

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ) Makefile
	@printf "\r\033[38;5;46m⌛ [$(NAME)]: 100%% ████████████████████❙ \\033[0m"
	@printf "\nSources are ready to be used !\n"
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFT) $(OPEN) -lft $(INC) $(LSDL2)

$(OBJ_PATH) :
	@mkdir -p $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(160 196 202 208 215 221 226 227 190 154 118 82 46);index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r\033[38;5;%dm⌛ [%s]: %2d%% `printf '█%.0s' {0..$(DONE)}`%*s❙%*.*s\033[0m\033[K" $(COLOR) $(NAME) $(PERCENT) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(CC) -MMD $(CFLAGS) $(INC) -o $@ -c $<
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:
	make -C $(LIBFT) clean
	@if [ -e $(OBJ_PATH) ]; \
	then \
		rm -rf $(OBJ_PATH); \
		printf "\r\033[38;5;202m✗ clean $(NAME).\033[0m\033[K\n"; \
	fi;
	@if [ -e $(NAME).dSYM/ ]; \
	then \
		rm -rf $(NAME).dSYM/; \
		printf "\r\033[38;5;202m✗ clean $(NAME).dSYM\033[0m\033[K\n"; \
	fi;

fclean: clean
	make -C $(LIBFT) fclean
	@if [ -e $(NAME) ]; \
	then \
		rm -f $(NAME); \
		printf "\r\033[38;5;196m✗ fclean $(NAME).\033[0m\033[K\n"; \
	fi;

run: all
	clear
	./wolf3d

lldb:
	gcc ./srcs/*.c $(INC) $(CFLAGS) $(LIB) $(LSDL2) $(FRK) $(OPEN) -o $(NAME) \
		-L$(LIBFT) -lft
	lldb ./wolf3d

fsani:
	gcc ./srcs/*.c $(INC) $(CFLAGS) -fsanitize=address \
		$(LIB) $(LSDL2) $(FRK) $(OPEN) $(FRK) $(APPK) -o $(NAME) \
		-L$(LIBFT) -lft
	./wolf3d

valg:
	gcc ./srcs/*.c $(INC) $(CFLAGS) \
	$(LIB) $(LSDL2) $(FRK) $(OPEN) -o $(NAME) \
	-L$(LIBFT) -lft
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=definite ./wolf3d

re: fclean all
