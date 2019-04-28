# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 16:21:49 by jsauron           #+#    #+#              #
#    Updated: 2019/04/28 17:45:49 by fmadura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= doom
CC 				= gcc
CFLAGS 			= -g
LEN_NAME		= `printf "%s" $(NAME) | wc -c`
DELTA			= $$(echo "$$(tput cols)-32-$(LEN_NAME)"|bc)
MAKEFLAGS		= --jobs=16
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
VPATH		:= ./srcs
OBJ_PATH 	= ./objs/
INC_PATH	= ./includes/

SDL_LIB		= -I ~/.brew/Cellar/sdl2/2.0.9_1/include/SDL2/ \
			-L ~/.brew/Cellar/sdl2/2.0.9_1/lib/ -lSDL2

UNAME 		:= $(shell uname)

SRC_NAME 	= tga_index.c \
				tga_map.c \
				tga_pos.c \
				tga_rle.c \
				tga_utils.c \
				tga_read.c

OBJ_NAME	= $(SRC_NAME:.c=.o)

OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC			= $(addprefix -I , $(INC_PATH)) $(addprefix -I , $(INC_PATH))
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
	@$(CC) $(CFLAGS) $(SDL_LIB) $(INC) $(OBJ) -o $(NAME)


$(OBJ_PATH) :
	@mkdir -p $@

$(OBJ_PATH)%.o: %.c | $(OBJ_PATH)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(160 196 202 208 215 221 226 227 190 154 118 82 46);index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r\033[38;5;%dm⌛ [%s]: %2d%% `printf '█%.0s' {0..$(DONE)}`%*s❙%*.*s\033[0m\033[K" $(COLOR) $(NAME) $(PERCENT) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(CC) -MMD $(SDL_LIB) $(CFLAGS) $(INC) -o $@ -c $<
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:
	rm -rf ./objs