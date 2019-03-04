# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 00:22:44 by abaille           #+#    #+#              #
#    Updated: 2019/03/04 14:10:51 by fmadura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= doom
CC 				= gcc
CFLAGS 			= -Wall -Wextra -Werror -g
LIBFT 			= ./libft
LEN_NAME		= `printf "%s" $(NAME) |wc -c`
DELTA			= $$(echo "$$(tput cols)-32-$(LEN_NAME)"|bc)

#color
YELLOW			= "\\033[33m"
BLUE			= "\\033[34m"
RED				= "\\033[31m"
WHITE			= "\\033[0m"
CYAN			= "\\033[36m"
GREEN			= "\\033[32m"
BOLD			= "\\033[1m"
PINK			= "\\033[95m"

OK				= $(CYAN)OK$(WHITE)
WAIT			= $(RED)WAIT$(WHITE)

ID_UN 		= $(shell id -un)
CELLAR		= /Users/$(ID_UN)/.brew/Cellar
VPATH		:= ./srcs:./srcs/engine:./srcs/math:./srcs/ui:./srcs/parsing
OBJ_PATH 	= ./objs/
INC_PATH	= ./includes/ \
			  ./libft/includes/

UNAME 		:= $(shell uname)

ifeq ($(UNAME), Linux)
CC 			= clang -std=c99
INC_PATH 	+= /usr/include/SDL2/
OPEN 		= -L/usr/lib/x86_64-linux-gnu -lm -lpthread
else
SDL_V		= $(shell ls $(CELLAR)/sdl2/ | head -1)
INC_PATH 	+= $(CELLAR)/sdl2/$(SDL_V)/include/SDL2/
INC_PATH 	+= $(CELLAR)/sdl2/$(SDL_V)/include/

SDL_TTF		= $(shell ls $(CELLAR)/sdl2_ttf/ | head -1)
INC_PATH 	+= $(CELLAR)/sdl2_ttf/$(SDL_TTF)/include/

SDL_IMG		= $(shell ls $(CELLAR)/sdl2_image/ | head -1)
INC_PATH 	+= $(CELLAR)/sdl2_image/$(SDL_IMG)/include/

SDL_MIX		= $(shell ls $(CELLAR)/sdl2_mixer/ | head -1)
INC_PATH 	+= $(CELLAR)/sdl2_mixer/$(SDL_MIX)/include/
endif

HED_NAME	= doom.h \
			  doom_s_assets.h \
			  doom_s_env.h \
			  doom_s_math.h \
			  doom_s_gameplay.h \
			  doom_s_engine.h \
			  doom_f_engine.h \
			  doom_f_math.h \
			  doom_define.h

SRC_NAME 	= main.c \
			load.c \
			loop.c \
			no_op.c \
			queue.c \
			map.c \
			hull.c \
			edge.c \
			vertex.c \
			utils_vertex.c \
			utils_edge.c \
			utils_pixels.c \
			utils_surface.c \
			transformation.c \
			move.c \
			draw.c \
			struct_drawline.c \
			struct_container.c \
			projection.c \
			checking.c \
			unload.c

OBJ_NAME	= $(SRC_NAME:.c=.o)
LSDL2		= -L/Users/$(ID_UN)/.brew/lib/ \
			  -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC			= $(addprefix -I , $(INC_PATH))
DIR			= $(sort $(dir $(OBJ)))
NB			= $(words $(SRC_NAME))
INDEX		= 0
HEAD		= $(addprefix ./includes/,$(HED_NAME))

SHELL		:=	bash

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ) $(HEAD) Makefile
	@printf "\r\033[38;5;46m⌛ [$(NAME)]: 100%% ████████████████████❙ \\033[0m"
	@printf "\nSources are ready to be used !\n"
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(INC) $(LSDL2) $(OBJ) -o $(NAME) -L$(LIBFT) $(OPEN) -lft

$(OBJ_PATH) :
	@mkdir -p $@

$(OBJ_PATH)%.o: %.c | $(OBJ_PATH)
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
	./doom

lldb:
	gcc ./srcs/**/*.c $(CFLAGS) $(LIB) $(LSDL2) $(FRK) $(OPEN) -o $(NAME) \
		-L$(LIBFT) -lft
	lldb ./doom

re: fclean all
