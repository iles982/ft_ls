# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/13 17:58:58 by tclarita          #+#    #+#              #
#    Updated: 2020/02/21 22:31:20 by tclarita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_ls.c parse.c get_flags.c tools.c tools_2.c sort.c

OBJ = $(SRC:.c=.o)

HEADER = ft_ls.h

FLAGS = -Wall -Werror -Wextra -I $(HEADER)
LIBFT = ft_printf
COLOR = \033[2;14m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(SRC)
		@make -C $(LIBFT)
		@gcc -c $(SRC)
		@gcc -o $(NAME) $(FLAGS) $(OBJ) ft_printf/libftprintf.a
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
