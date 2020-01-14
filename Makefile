# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/13 17:58:58 by tclarita          #+#    #+#              #
#    Updated: 2020/01/14 20:01:03 by tclarita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c

OBJ = $(SRC:.c=.o)

HEADER = ft_ls.h

FLAGS = -Wall -Werror -Wextra -I $(HEADER)
LIBFT = libft
COLOR = \033[2;14m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(SRC)
		@make -C $(LIBFT)
		@gcc -c $(SRC)
		@gcc -o $(NAME) $(FLAGS) $(OBJ) libft/libft.a
		@make clean -silent
		@echo "$(COLOR)Lem_in successfully compiled"

%.o : %.c
		@echo "$(NAME) >>> Add/Update $^"

clean:
		@rm -rf $(OBJ)
		@make clean -C $(LIBFT)

fclean: clean
		@rm -rf $(NAME)
		@make fclean -C $(LIBFT)

re: fclean all
