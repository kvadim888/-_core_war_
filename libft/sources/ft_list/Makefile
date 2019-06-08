# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/09 18:37:18 by vkryvono          #+#    #+#              #
#    Updated: 2018/10/10 21:40:36 by vkryvono         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ../../src.mk

SRC_PATH	=	.
INC_PATH	=	../../includes
OBJ_PATH	=	../../objects

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

INC			=	-I $(INC_PATH)
OBJ			=	$(addprefix $(OBJ_PATH)/, $(SRC_LIST:.c=.o))

ft_list: $(OBJ)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	$(CC) $(INC) -o $@ -c $< $(FLAGS)
