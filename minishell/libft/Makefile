# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 16:17:00 by albaur            #+#    #+#              #
#    Updated: 2022/04/22 07:28:49 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strcpy.c \
ft_printf.c ft_putstr.c ft_putptr.c ft_putnbr.c ft_putchar.c ft_itohex.c \
ft_putint_unsigned.c ft_putchar_fd.c ft_itoa.c get_next_line.c \
get_next_line_utils.c ft_getlastint.c
SRCBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJ = $(SRC:.c=.o)
OBJBONUS = $(SRCBONUS:.c=.o)

$(NAME): $(OBJ)
				ar rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(OBJBONUS)
				ar rcs $(NAME) $(OBJ) $(OBJBONUS)

all: $(NAME)

clean:
				$(RM) $(OBJ) $(OBJBONUS)

fclean: clean
				$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
