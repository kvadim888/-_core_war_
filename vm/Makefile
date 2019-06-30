

NAME = corewar

FLAGS = -Wall -Werror -Wextra

INCLUDES =  ../includes/functions.h\
            ../includes/op.h\
            ../includes/vm.h\
            ../libft/includes/libft.h

SRC =   alert.c\
        func_fork.c\
        func_ld.c\
        func_math.c\
        func_misc.c\
        func_st.c\
        functions.c\
        game.c\
        init_champion.c\
        logger.c\
        main.c\
        utilities.cc


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
	make clean -C ../libft/

fclean: clean
	make fclean -C ../libft/
	rm -rf $(NAME)

re: fclean all