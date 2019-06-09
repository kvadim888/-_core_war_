NAME = funct_test

FLAGS = -Wall -Werror -Wextra

FUNCTIONS =  main.c helpers1.c

LIBFT = ../libft/libft.a

COMPILED = $(FUNCTIONS:.c=.o)

HEADERS = functions.h

all: $(NAME)

$(NAME): $(COMPILED) $(LIBFT)
	@gcc $(FLAGS) -o $(NAME) $(COMPILED) $(LIBFT)

$(LIBFT):	liball

liball:
	@make -C ../libft
	
clean:
	@rm -f *.o
	make clean -C ../libft/

fclean: clean
	make fclean -C ../libft/
	rm -rf $(NAME)

re: fclean all
