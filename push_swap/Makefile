# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 11:12:36 by albaur            #+#    #+#              #
#    Updated: 2022/04/08 18:25:01 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC = ./srcs/push_swap.c ./srcs/sanity_check.c ./srcs/push_swap_get_num.c \
./srcs/push_swap_op_push.c ./srcs/push_swap_op_swap.c \
./srcs/push_swap_op_rotate.c ./srcs/push_swap_op_reverse_rotate.c \
./srcs/push_swap_algo.c ./srcs/push_swap_algo_2.c \
./libft/ft_atoi.c ./libft/ft_split.c ./libft/ft_strlen.c ./libft/ft_strdup.c \
./libft/ft_printf.c ./libft/ft_itohex.c ./libft/ft_putchar.c \
./libft/ft_putstr.c ./libft/ft_putint_unsigned.c ./libft/ft_putnbr.c \
./libft/ft_putptr.c ./libft/ft_itoa.c ./libft/ft_putchar_fd.c \
./libft/ft_bzero.c ./libft/ft_strtololo.c ./libft/ft_intlen.c \
./libft/ft_dectobin.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
				gcc -o $(NAME) $(OBJ) $(CFLAGS)

%.o: %.c
				$(CC) -I. ${INCLUDES} -o $@ -c $? $(CFLAGS)

all: $(NAME)

clean:
				$(RM) $(OBJ)

fclean: clean
				$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
