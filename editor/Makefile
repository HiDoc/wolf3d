# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/14 15:53:53 by sgalasso          #+#    #+#              #
#    Updated: 2019/05/08 14:31:58 by sgalasso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	editor
CC			=	gcc
CFLAGS 		=	-Wall -Wextra -Werror -g -fsanitize=address

ID_UN 		=	$(shell id -un)
VPATH       =	./srcs:./srcs/ui_functions:./srcs/display:srcs/events \
	:srcs/utils:./srcs/init:./srcs/create_delete:./srcs/release:./srcs/events/click_functions
OBJ_PATH 	=	objs/
INC_PATH	=	includes/ \
				libft/includes/
LIBFT 		=	libft/

WHITE       =	"\\033[0m"
CYAN        =	"\\033[36m"
GREEN       =	"\\033[32m"

SDL_NUM		=	$(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2/ | tail -1)
TTF_NUM		=	$(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/ | tail -1)
IMG_NUM		=	$(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2_image/ | tail -1)
MIX_NUM		=	$(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/ | tail -1)

INC_PATH	+=	/Users/$(ID_UN)/.brew/Cellar/sdl2/$(SDL_NUM)/include/ \
				/Users/$(ID_UN)/.brew/Cellar/sdl2/$(SDL_NUM)/include/SDL2/ \
				/Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/$(TTF_NUM)/include/ \
				/Users/$(ID_UN)/.brew/Cellar/sdl2_image/$(IMG_NUM)/include/ \
				/Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/$(MIX_NUM)/include/ \

SRC_NAME 	=	main.c \
				ui_exit_sdl.c \
				ui_error_exit_sdl.c \
				ui_get_events.c \
				ui_init_sdl.c \
				ui_make_window.c \
				ui_make_surface.c \
				ui_make_rect.c \
				ui_make_full_rect.c \
				ui_make_line.c \
				ui_make_clipped_line.c \
				ui_draw_vector.c \
				ui_make_dotted_line.c \
				ui_make_input.c \
				ui_set_pixel.c \
				ui_make_frame.c \
				ui_gameloop.c \
				ui_make_circle.c \
				ui_load_font.c \
				ui_make_string.c \
				ui_make_nbrstring.c \
				ui_hex_to_rgb.c \
				ui_mouseenter.c \
				ui_close_to.c \
				ui_load_image.c \
				menu.c \
				editor.c \
				draw_mode.c \
				select_mode.c \
				move_mode.c \
				elem_mode.c \
				handle_events.c \
				utils.c \
				utils_math.c \
				utils_display.c \
				targetting.c \
				vertex_in_sector.c \
				display_interface.c \
				display_selection.c \
				display_drawing.c \
				display_element.c \
				menu_events.c \
				get_element.c \
				export_map.c \
				init_env.c \
				create_object.c \
				create_vertex.c \
				create_w_vertex.c \
				create_sector.c \
				delete_object.c \
				delete_sector.c \
				delete_vertex.c \
				delete_w_vertex.c \
				delete_edge.c \
				crs_del.c \
				dir_del.c \
				msc_del.c \
				rdr_del.c \
				srf_del.c \
				ttf_del.c \
				txr_del.c \
				wdw_del.c \
				click_obj_panel.c \
				click_vtx_panel.c \
				click_sct_panel.c \
				click_edg_panel.c \
				click_msc_panel.c \

OBJ_NAME	=	$(SRC_NAME:.c=.o)
LSDL2		=	-L/Users/$(ID_UN)/.brew/lib/ \
				-lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image

SRC			=	$(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC			=	$(addprefix -I, $(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@Make -C $(LIBFT)
	@printf "$(CYAN)[WAIT]$(WHITE) Compiling into %-50s\r" $(NAME)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFT) -lft $(INC) $(LSDL2)
	@printf "$(GREEN)[OK]$(WHITE) %s has been well compiled\n" $(NAME)

$(OBJ) : | $(OBJ_PATH)

$(OBJ_PATH) :
	@mkdir objs

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_PATH) Makefile
	@printf "$(CYAN)[WAIT]$(WHITE) Compiling into .o %-50s\r" $@
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(OBJ_PATH)
	@printf "$(GREEN)[OK]$(WHITE) Clean done\n"

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)
	@printf "$(GREEN)[OK]$(WHITE) Fclean done\n"

re: fclean all

.PHONY: all re clean fclean
