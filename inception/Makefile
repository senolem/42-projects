# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 11:47:12 by faventur          #+#    #+#              #
#    Updated: 2022/07/26 15:32:22 by faventur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#		( ͡° ͜ʖ ͡°)			COMPILATION			( ͡° ͜ʖ ͡°)

NAME = inception
SRC_PATH = srcs/
COMPOSE = $(SRC_PATH)/docker-compose.yml
ENV = $(SRC_PATH)/.ENV
FLAGS = -f $(COMPOSE) -p $(NAME)

#		(҂◡_◡)			UTILS			(҂◡_◡)

RM = rm -rf

#		(｡◕‿◕｡)			COLORS			(｡◕‿◕｡)

NONE = \033[0m
HIRED = \033[31m
HIGREEN = \033[92m
HIBLUE = \033[94m
CURSIVE = \033[3m

#		( ಠ ʖ̯ ಠ)		RULES			( ಠ ʖ̯ ಠ)

all: build

build:
	@docker-compose $(FLAGS) up -d --build

start:
	@docker-compose ${FLAGS} start

stop:
	@docker-compose ${FLAGS} stop

clean:
	@rm -rf data/*

fclean: clean
	#todo

re: stop fclean all

.phony: all build start stop clean fclean re
