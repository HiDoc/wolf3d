NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS_PATH = ./srcs/
OBJS_PATH = ./objects/

YELLOW		= "\\033[33m"
BLUE		= "\\033[34m"
RED			= "\\033[31m"
WHITE		= "\\033[0m"
CYAN		= "\\033[36m"
GREEN		= "\\033[32m"
BOLD		= "\\033[1m"
PINK		= "\\033[95m"

SRCS_NAME =	ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_atoi.c \
			ft_itoa.c \
			ft_strlen.c \
			ft_nbrlen.c \
			ft_nbwords.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_memdel.c \
			ft_strdel.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_memalloc.c \
			ft_strdup.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_sq.c \
			ft_pow.c \
			ft_sqrt.c \
			ft_abs.c \
			get_next_line.c \
			lifetime.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(subst $(SRCS_PATH), $(OBJS_PATH), $(SRCS:.c=.o))
INCLUDES = includes/

#.SILENT:

all:	$(NAME)

$(NAME):    $(OBJS)
	@printf "$(CYAN)[WAIT]$(WHITE) Compiling into %-50s\r" $(NAME)
	@ar rc $(NAME) $(OBJS) && ranlib $(NAME)
	@printf "$(GREEN)[OK]$(WHITE) %s has been well compiled\n" $(NAME)

$(OBJS) : | $(OBJS_PATH)

$(OBJS_PATH):
	@mkdir objects

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INCLUDES)libft.h Makefile
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	@/bin/rm -rf objects/

fclean:	clean
	@/bin/rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
