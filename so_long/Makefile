# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/14 14:50:45 by albaur            #+#    #+#              #
#    Updated: 2022/11/29 10:23:42 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC = ./srcs/so_long.c ./srcs/render.c ./srcs/initialization.c ./srcs/hook.c \
./srcs/map.c ./srcs/movement.c ./srcs/sanity_check.c ./srcs/utilities.c \
./srcs/lst_utilities.c ./srcs/render_2.c ./srcs/movement_2.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
			@$(MAKE) -sC ./libft
			@mv ./libft/libft.a .
			$(CC) $(CFLAGS) $(OBJ) libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) -fsanitize=address

%.o: %.c
			$(CC) $(CFLAGS) -Wall -Wextra -Werror -Imlx -c $< -o $@

all: $(NAME)

clean:
			$(RM) $(OBJ)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.phony: all clean fclean re


