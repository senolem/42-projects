# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 11:47:12 by faventur          #+#    #+#              #
#    Updated: 2023/02/09 14:41:52 by albaur           ###   ########.fr        #
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

all: refresh


build:
	@docker-compose $(FLAGS) build

start:
	@docker-compose ${FLAGS} start

stop:
	@docker-compose ${FLAGS} stop

refresh:
	@docker-compose $(FLAGS) up -d --build

clean: stop
	sudo rm -rf ~/data/www/* && sudo rm -rf ~/data/mariadb/*

fclean: stop clean
	docker system prune -f

re: stop fclean all

.phony: all build start stop refresh clean fclean re
