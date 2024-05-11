# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 11:47:12 by faventur          #+#    #+#              #
#    Updated: 2023/10/03 20:53:57 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#		( ͡° ͜ʖ ͡°)			COMPILATION			( ͡° ͜ʖ ͡°)

NAME = transcendance
SRC_PATH = srcs/
DOCKERFILE = ./Dockerfile
PORT = 3000
FLAGS =
FRONTEND_PATH = ./frontend
BACKEND_PATH = ./backend
FRONTEND_SCRIPT = run serve
BACKEND_SCRIPT = run start:dev

#		(O_O)			ENV				(O_O)

include ./frontend/.env
include ./backend/.env
include ./database/.env
export

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

db:
	@mkdir -p $(PWD)/database/data/postgres
	@docker-compose $(FLAGS) up -d --build database

front:
	@npm --prefix $(FRONTEND_PATH) install
	@npm --prefix $(FRONTEND_PATH) $(FRONTEND_SCRIPT)

front-container:
	@docker-compose $(FLAGS) up -d --build frontend

back:
	@npm --prefix $(BACKEND_PATH) install
	@npm --prefix $(BACKEND_PATH) $(BACKEND_SCRIPT)

back-container:
	@mkdir -p $(PWD)/backend/data/avatar
	@mkdir -p $(PWD)/backend/data/background
	@mkdir -p $(PWD)/backend/data/gameBackground
	@mkdir -p $(PWD)/backend/data/music
	@mkdir -p $(PWD)/backend/data/thumbnail
	@docker-compose $(FLAGS) up -d --build backend

nginx-container:
	@docker-compose $(FLAGS) up -d --build nginx

clean: stop
	$(RM) ./backend/dist
	$(RM) ./frontend/dist

fclean: stop clean
	docker system prune -f
	docker rmi transcendance_frontend transcendance_backend transcendance_database -f
	$(RM) ./database/data/*
	$(RM) ./backend/node_modules
	$(RM) ./frontend/node_modules
	
re: stop fclean all

.phony: all build start stop refresh clean fclean re db front back front-container back-container
