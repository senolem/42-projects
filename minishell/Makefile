# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 14:39:13 by albaur            #+#    #+#              #
#    Updated: 2022/06/17 11:48:49 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRC = ./srcs/minishell.c ./srcs/init.c ./srcs/parsing.c \
./srcs/utils.c ./srcs/signal.c ./srcs/env.c \
./libft/ft_printf.c ./libft/ft_itohex.c ./libft/ft_putchar.c \
./libft/ft_putnbr.c ./libft/ft_putint_unsigned.c ./libft/ft_putptr.c \
./libft/ft_putstr.c ./libft/ft_itoa.c ./libft/ft_putchar_fd.c \
./libft/ft_intlen.c ./libft/ft_strdup.c ./libft/ft_strlen.c ./libft/ft_split.c \
./libft/ft_memset.c ./libft/ft_lstadd_back.c ./libft/ft_lstnew.c \
./libft/ft_isspace.c ./libft/ft_arrdup.c ./libft/ft_arrdup_after.c \
./libft/ft_arrdup_before.c ./libft/ft_arrjoin.c ./libft/ft_concat.c \
./libft/ft_putendl_fd.c ./libft/ft_strcmp.c ./libft/ft_strjoin.c \
./libft/ft_strncmp.c ./libft/ft_arrlen.c ./libft/ft_arrndup.c \
./libft/ft_calloc.c ./libft/ft_memcpy.c ./libft/ft_arrfree.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
			$(CC) -lreadline -o $(NAME) $(OBJ) $(CFLAGS)

clean:
			$(RM) $(OBJ)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.phony: all clean fclean re