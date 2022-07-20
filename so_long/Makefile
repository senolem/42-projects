# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/14 14:50:45 by albaur            #+#    #+#              #
#    Updated: 2022/04/25 15:32:13 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC = ./srcs/so_long.c ./srcs/render.c ./srcs/initialization.c ./srcs/hook.c \
./srcs/map.c ./srcs/movement.c ./srcs/sanity_check.c ./srcs/utilities.c \
./srcs/lst_utilities.c ./srcs/render_2.c ./srcs/movement_2.c \
./libft/ft_printf.c ./libft/ft_putchar.c ./libft/ft_itohex.c \
./libft/ft_putnbr.c ./libft/ft_putstr.c ./libft/ft_putptr.c \
./libft/ft_putint_unsigned.c ./libft/ft_putchar_fd.c ./libft/ft_itoa.c \
./libft/ft_intlen.c ./libft/ft_strlen.c ./libft/ft_strjoin.c \
./libft/get_next_line.c ./libft/get_next_line_utils.c ./libft/ft_strrchr.c \
./libft/ft_strncmp.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
			$(CC) $(CFLAGS) -Wall -Wextra -Werror -Imlx -c $< -o $@

all: $(NAME)

clean:
			$(RM) $(OBJ)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.phony: all clean fclean re


