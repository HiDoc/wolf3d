CC = gcc
VPATH = ./../../libft:./../../includes
LIBFT = -L ../../libft -lft
INC = -I ../../libft/includes -I ./../../includes
all: parser

SRC = parser.c token.c comparison.c
OBJ = $(SRC:.c=.o)
NAME = parser
all: $(NAME)

$(NAME):
	$(CC) $(SRC) $(INC) $(CFLAGS) $(LIB) -o parser $(LIBFT)
	./parser map.txt

$(OBJ)%.o: %.c
