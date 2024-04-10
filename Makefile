NAME = pipex

CC = cc

CFLAGS = -Werror -Wextra -Wall

SRC = main.c

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
	@rm $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all
