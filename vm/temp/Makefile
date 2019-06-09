NAME = funct

FLAGS = -Wall -Werror -Wextra

FUNCTIONS =  main.c read_params.c recognize_op.c recognize_op2.c initialize_op.c \
	create_process.c cr_live.c check_codage.c check_old_process.c \
	func/ld.c func/live.c func/st.c

LIBFT = libft/libft.a

COMPILED = $(FUNCTIONS:.c=.o)

HEADERS = functions.h

all: $(NAME)

$(NAME): $(COMPILED) $(LIBFT)
	@gcc $(FLAGS) -o $(NAME) $(COMPILED) $(LIBFT)

$(LIBFT):	liball

liball:
	@make -C ./libft
	
clean:
	@rm -f *.o
	make clean -C libft/

fclean: clean
	make fclean -C libft/
	rm -rf $(NAME)

re: fclean all
