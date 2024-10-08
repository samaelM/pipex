NAME = pipex

CC = clang

CFLAGS = -Werror -Wextra -Wall -g

SRC = src/pipex.c src/pipex_utils.c src/ft_token.c src/ft_strtrimtoken.c

OBJ = $(SRC:.c=.o)

LIBFTDIR = ./libft/

LIBFTNAME = libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	@make -s -C $(LIBFTDIR)
	@$(CC) $(OBJ) $(LIBFTDIR)$(LIBFTNAME) -o $(NAME)

.c.o :
	@$(CC) $(CFLAGS) -g -c -o $@ $<

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)
	@make -s -C $(LIBFTDIR) fclean

re : fclean all
