# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 10:38:31 by albaur            #+#    #+#              #
#    Updated: 2022/04/20 11:44:23 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVERNAME = server
CLIENTNAME = client
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SERVERSRC = ./srcs/server.c
CLIENTSRC = ./srcs/client.c
SRC = ./libft/ft_printf.c ./libft/ft_itohex.c ./libft/ft_putchar.c \
./libft/ft_putint_unsigned.c ./libft/ft_putnbr.c ./libft/ft_putptr.c \
./libft/ft_putstr.c ./libft/ft_itoa.c ./libft/ft_putchar_fd.c \
./libft/ft_atoi.c ./libft/ft_intlen.c
SERVEROBJ = $(SERVERSRC:.c=.o) $(SRC:.c=.o)
CLIENTOBJ = $(CLIENTSRC:.c=.o) $(SRC:.c=.o)

all: $(SERVERNAME) $(CLIENTNAME)

$(SERVERNAME): $(SERVEROBJ)
				gcc -o $(SERVERNAME) $(SERVEROBJ) $(CFLAGS)

$(CLIENTNAME): $(CLIENTOBJ)
				gcc -o $(CLIENTNAME) $(CLIENTOBJ) $(CFLAGS)

clean:
				$(RM) $(SERVEROBJ) $(CLIENTOBJ)

fclean: clean
				$(RM) $(SERVERNAME) $(CLIENTNAME)

re: fclean all

.PHONY: all clean fclean re
