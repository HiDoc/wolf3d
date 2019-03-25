# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 00:22:44 by abaille           #+#    #+#              #
#    Updated: 2019/03/25 12:32:32 by jsauron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= doom
CC 				= gcc
CFLAGS 			= -Wall -Wextra -Werror -g #-O3 -fsanitize=address
LIBFT 			= ./libft
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
CELLAR		= /Users/$(ID_UN)/.brew/Cellar
VPATH		:= ./srcs:./srcs/engine:./srcs/math:./srcs/ui:./srcs/parsing:./srcs/debug:./srcs/gameplay:./srcs/tga_reader
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
			  doom_s_tga_reader.h \
			  doom_f_engine.h \
			  doom_f_math.h \
			  doom_f_ui.h \
			  doom_define.h \
			  doom_f_tga_reader.h \

SRC_NAME 	= main.c \
			load.c \
			loop.c \
			loop_frames.c \
			no_op.c \
			queue.c \
			sdl_hook.c \
			utils.c \
			sdl_mouse.c \
			musics.c \
			edge.c \
			function.c \
			vertex.c \
			utils_vertex.c \
			utils_pixels.c \
			map.c \
			hull.c \
			utils_edge.c \
			utils_surface.c \
			transformation.c \
			move.c \
			position.c \
			draw.c \
			print_bug.c \
			struct_drawline.c \
			struct_container.c \
			projection.c \
			checking.c \
			unload.c \
			struct_img.c \
			utils_img.c \
			struct_character.c \
			struct_object.c \
			parse_objects.c \
			action_object.c \
			action_pl_object.c \
			action_pl_weapon.c \
			struct_inventory.c \
			action_inventory.c \
			draw_inventory.c \
			weapons_inventory.c \
			utils_draw_inventory.c \
			struct_weapon.c \
			utils_weapons.c \
			utils_ui.c \
			struct_hud.c \
			draw_hud.c 	\
			utils_color.c \
			ui_minimap.c \
			ui_make_surface.c \
			ui_draw_line.c \
			ui_draw_vector.c \
			ui_draw_rect.c \
			ui_draw_full_rect.c \
			ui_draw_circle.c \
			ui_draw_full_circle.c \
			ui_draw_string.c \
			data_color.c \
			ft_strjoin2.c \
			load_tga.c \
			read_data.c \
			rle_color.c \
			rle.c \
			set_data_pxl.c \
			set_pxl_color.c \
			tga_main.c \

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

norminette:
	norminette \
	-R CheckCommentsFormat \
	-R CheckMultipleEmptyLines \
	-R CheckCppComment \
	-R CheckCommentsPlacement \
	srcs/**.c

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
parser:
	$(CC) parser.c $(CFLAGS) $(LIB) $(INC) -o parser -L$(LIBFT) -lft
	./parser map.txt
run: all
	clear
	./doom

lldb:
	gcc ./srcs/**/*.c $(CFLAGS) $(LIB) $(LSDL2) $(FRK) $(OPEN) -o $(NAME) \
		-L$(LIBFT) -lft
	lldb ./doom

re: fclean all
