# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 14:34:59 by albaur            #+#    #+#              #
#    Updated: 2021/11/29 12:03:51 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= srcs/ft_putchar.c srcs/ft_swap.c srcs/ft_putstr.c srcs/ft_strlen.c srcs/ft_strcmp.c
OBJS	= ${SRCS:.c=.o}
INCL	= includes
SPATH	= srcs
NAME	= libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
LIBA	= ar rc
LIBR	= ranlib

${NAME} :	${OBJS}
			${LIBA} ${NAME} ${OBJS}
			${LIBR} ${NAME}

.c.o :		
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCL}

all :		${NAME}

clean :
			${RM} ${OBJS}

fclean :	clean
			${RM} ${NAME}

re :		fclean all
