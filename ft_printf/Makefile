# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 17:52:57 by tclarita          #+#    #+#              #
#    Updated: 2020/02/03 06:22:21 by tclarita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = tools.c tools_2.c tools_3.c ft_printf.c flags.c c.c int.c o.c p.c s.c \
checks.c u.c x.c xx.c tools_4.c tools_5.c int_2.c f.c f_2.c

OFILES = $(SRC:.c=.o)

HEADER = ft_printf.h

FLAGS = -Wall -Werror -Wextra

LIBFT = libft

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OFILES) $(SRC)
		@make -C $(LIBFT)
		@cp libft/libft.a ./$(NAME)
		gcc -c $(SRC) -I $(HEADER) $(FLAGS)
		ar rc $(NAME) $(OFILES)
		ranlib $(NAME)

%.o : %.c
		@echo "$(NAME) >>> Add/Update $^"

clean:
	@rm -f $(OFILES)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all