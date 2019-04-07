CC = gcc
VPATH = ./../../libft:./../../
LIBFT = -L ../../libft -lft
INC = -I ../../libft/includes -I ./../../includes
all: parser

SRC = parser.c token.c lexer.c printer.c op.c reader.c
OBJ = $(SRC:.c=.o)
NAME = ast
all: $(NAME)

$(NAME):
	$(CC) $(SRC) $(INC) $(CFLAGS) $(LIB) -o parser $(LIBFT)
	./parser map.txt