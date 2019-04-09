CC 			= gcc
CFLAGS 		= -g
NAME 		= ast

VPATH 		= ./../../libft:./../../:./srcs

LIBFT 		= -L ../../libft -lft

INC 		= -I ../../libft/includes \
			-I ./includes \
			-I ../../includes \
			-I ~/.brew/include/SDL2 \
			-L ~/.brew/lib/

SRC_NAME 	=	op.c \
				parser.c \
				token.c \
				lexer.c \
				printer.c \
				reader.c \
				line.c

OBJ_PATH	= ./objs/
OBJ_NAME	= $(SRC_NAME:.c=.o)

BREW_SDL	= ~/.brew/Cellar/sdl2
BREW_TTF	= ~/.brew/Cellar/sdl2_ttf
BREW_FT		= ~/.brew/Cellar/freetype
BREW_IMG	= ~/.brew/Cellar/sdl2_image
BREW_MIX	= ~/.brew/Cellar/sdl2_mixer
BREW		= $(BREW_SDL) $(BREW_TTF) $(BREW_IMG) $(BREW_MIX)
SDL_LIB		= -lSDL2_ttf -lSDL2 -lSDL2_mixer -lSDL2_image

OBJS		= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(SDL_LIB) $(INC) $(LIBFT) -o $(NAME)

$(OBJ_PATH)%.o: %.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(OBJS)