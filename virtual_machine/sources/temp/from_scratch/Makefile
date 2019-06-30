NAME = funct_test

FLAGS = -Wall -Werror -Wextra

FUNCTIONS =  main.c helpers1.c champ_main.c process_arg.c create_map.c cycle.c recognize_op.c

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
