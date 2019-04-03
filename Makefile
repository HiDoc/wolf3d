# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsauron <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 16:21:49 by jsauron           #+#    #+#              #
#    Updated: 2019/04/01 16:23:28 by jsauron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= doom
CC 				= gcc
CFLAGS 			= -Wall -Wextra -Werror -g
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
VPATH		:= ./srcs:./srcs/engine:./srcs/math:./srcs/ui:./srcs/parsing:./srcs/debug:./srcs/gameplay:./srcs/hud
OBJ_PATH 	= ./objs/
INC_PATH	= ./includes/ \
			  ./libft/includes/	\

BREW		= ~/.brew
BREW_SDL	= ~/.brew/Cellar/sdl2
BREW_TTF	= ~/.brew/Cellar/sdl2_ttf
BREW_FT		= ~/.brew/Cellar/freetype
BREW_IMG	= ~/.brew/Cellar/sdl2_image
BREW_MIX	= ~/.brew/Cellar/sdl2_mixer

SDL_LIB		= -lSDL2_ttf -lSDL2 -lSDL2_mixer -lSDL2_image

UNAME 		:= $(shell uname)

ifeq ($(UNAME), Linux)
CC 			= clang -std=c99
INC_PATH 	+= /usr/include/SDL2/
OPEN 		= -L/usr/lib/x86_64-linux-gnu -lm -lpthread
endif

HED_NAME	= doom.h \
			  doom_s_assets.h \
			  doom_s_env.h \
			  doom_s_math.h \
			  doom_s_gameplay.h \
			  doom_s_engine.h \
			  doom_f_engine.h \
			  doom_f_math.h \
			  doom_f_ui.h \
			  doom_define.h

SRC_NAME 	= main.c \
			action_enemies.c \
			action_gems.c \
			action_inventory.c \
			action_object.c \
			action_pl_object.c \
			action_pl_weapon.c \
			checking.c \
			draw.c \
			draw_hud.c 	\
			draw_inventory.c \
			edge.c \
			function.c \
			handle_weapon.c \
			hud_data.c \
			hull.c \
			init.c \
			init_enemies.c \
			init_minimap.c \
			init_skybox.c \
			load.c \
			loop.c \
			map.c \
			move.c \
			musics.c \
			no_op.c \
			parse_enemies.c \
			parse_objects.c \
			perspective.c \
			position.c \
			print_bug.c \
			projection.c \
			queue.c \
			render_sect.c \
			sdl_hook.c \
			sdl_mouse.c \
			struct_character.c \
			struct_container.c \
			struct_drawline.c \
			struct_font.c \
			struct_hud.c \
			struct_hud_img.c \
			struct_inventory.c \
			struct_object.c \
			struct_weapon.c \
			transformation.c \
			ui_draw_circle.c \
			ui_draw_full_circle.c \
			ui_draw_full_rect.c \
			ui_draw_line.c \
			ui_draw_rect.c \
			ui_draw_string.c \
			ui_draw_vector.c \
			ui_make_surface.c \
			ui_minimap.c \
			unload.c \
			utils.c \
			utils_color.c \
			utils_edge.c \
			utils_hud_img.c \
			utils_pixels.c \
			utils_surface.c \
			utils_vertex.c \
			utils_weapons.c \
			vertex.c \
			weapons_inventory.c

OBJ_NAME	= $(SRC_NAME:.c=.o)

OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC			= $(addprefix -I , $(INC_PATH))
DIR			= $(sort $(dir $(OBJ)))
NB			= $(words $(SRC_NAME))
INDEX		= 0
HEAD		= $(addprefix ./includes/,$(HED_NAME))

SHELL		:=	bash

.PHONY: all re clean fclean

all: $(BREW) $(BREW_SDL) $(BREW_FT) $(BREW_TTF) $(BREW_MIX) $(BREW_IMG) COMPILE

$(NAME): $(OBJ_PATH) $(OBJ) $(HEAD) Makefile
	@printf "\r\033[38;5;46m⌛ [$(NAME)]: 100%% ████████████████████❙ \\033[0m"
	@printf "\nSources are ready to be used !\n"
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME) -L$(LIBFT) $(SDL2LIB) $(SDL_LIB) $(OPEN) -lft

COMPILE : sdl2lib sdl2cflags $(NAME)

sdl2lib:
		$(eval SDL2LIB = $(shell sdl2-config --libs))

sdl2cflags:
		$(eval SDL2CFLAGS = $(shell sdl2-config --cflags))

$(BREW) :
		$(shell /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)")
		brew upgrade
		brew -v install pkg-config


cleanbrew:
	brew uninstall -f sdl2_ttf
	brew uninstall -f freetype
	brew uninstall -f pkg-config
	brew uninstall -f libgpng
	brew uninstall -f sdl2_image
	brew uninstall -f sdl2_mixer
	brew uninstall -f sdl2

$(BREW_SDL) :
		brew -v install sdl2
$(BREW_FT) :
		brew -v install freetype
$(BREW_TTF) :
		brew -v install sdl2_ttf
$(BREW_MIX) :
		brew -v	install sdl2_mixer
$(BREW_IMG) :
		brew -v install sdl2_image

$(OBJ_PATH) :
	@mkdir -p $@

$(OBJ_PATH)%.o: %.c | $(OBJ_PATH)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(160 196 202 208 215 221 226 227 190 154 118 82 46);index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r\033[38;5;%dm⌛ [%s]: %2d%% `printf '█%.0s' {0..$(DONE)}`%*s❙%*.*s\033[0m\033[K" $(COLOR) $(NAME) $(PERCENT) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(CC) -MMD $(CFLAGS) $(INC) -o $@ -c $< $(SDL2CFLAGS)
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

fcleansdl: cleanbrew fclean

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

.NOTPARALLEL:
re: fclean all
