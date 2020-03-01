# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/13 17:58:58 by tclarita          #+#    #+#              #
#    Updated: 2020/03/01 05:50:41 by tclarita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_ls.c parse.c get_flags.c tools.c parse_data.c sort.c print.c make_ls.c

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
		@gcc -o $(NAME) $(FLAGS) $(OBJ) ft_printf/libftprintf.a -g
		@make clean -silent
		@echo "$(COLOR)FT_LS successfully compiled"

%.o : %.c
		@echo "$(NAME) >>> Add/Update $^"

clean:
		@rm -rf $(OBJ)
		@make clean -C $(LIBFT)

fclean: clean
		@rm -rf $(NAME)
		@make fclean -C $(LIBFT)

re: fclean all
