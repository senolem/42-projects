# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/30 11:06:29 by albaur            #+#    #+#              #
#    Updated: 2021/11/30 16:24:52 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ./srcs/ft_display_file.c
OBJS	= ${SRCS:.c=.o}
NAME	= ft_display_file
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

${NAME}	:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all		:	${NAME}

clean	:
			${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}
