NAME = corewar

FLAGS = -Wall -Werror -Wextra

VM =  main.c utilities.c logger.c functions.c alert.c init_champion.c func_math.c game.c func_st.c func_misc.c func_ld.c func_fork.c g_operations.c

INCLUDES = ../includes/functions.h ../includes/op.h ../includes/vm.h

LIBFT = ../libft/libft.a

COMPILED = $(VM:.c=.o)

HEADERS = functions.h

all: $(NAME)

$(NAME): $(COMPILED) $(LIBFT)
	@gcc $(FLAGS) -o $(NAME)  $(COMPILED) $(LIBFT)

$(LIBFT):	liball

liball:
	@make -C ../libft
	
clean:
	@rm -f *.o
	# make clean -C ../libft/

fclean: clean
	# make fclean -C ../libft/
	rm -rf $(NAME)

re: fclean all