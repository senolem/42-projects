# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 16:17:00 by albaur            #+#    #+#              #
#    Updated: 2022/04/11 15:53:35 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC = ft_printf.c ./srcs/ft_itohex.c ./srcs/ft_putchar.c ./srcs/ft_putnbr.c \
./srcs/ft_putint_unsigned.c ./srcs/ft_putptr.c ./srcs/ft_putstr.c \
./srcs/ft_itoa.c ./srcs/ft_putchar_fd.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
				ar rcs $(NAME) $(OBJ)

all: $(NAME)

clean:
				$(RM) $(OBJ)

fclean: clean
				$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
