# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 11:47:12 by faventur          #+#    #+#              #
#    Updated: 2023/01/25 23:28:00 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#		( ͡° ͜ʖ ͡°)			COMPILATION			( ͡° ͜ʖ ͡°)

NAME = test.a
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address
LINKS =
LIBLINKS = -I./includes -I../includes
SRC_PATH = srcs/
OBJ_PATH = bin/
C_EXTENSION = .cpp

#		눈_눈			SOURCES			눈_눈

UTILS_PATH		=	utils/
UTILS_FILES 	= 	compare_files file time
SRCS_FILES		+=	$(addprefix $(UTILS_PATH), $(UTILS_FILES))

VECTOR_PATH		=	vector/
VECTOR_FILES 	= 	constructor element_access iterators
SRCS_FILES		+=	$(addprefix $(VECTOR_PATH), $(VECTOR_FILES))

SRCS_FILES_EXT 		+= 	$(addsuffix $(C_EXTENSION), $(SRCS_FILES))
SRCS 				+= 	$(addprefix $(SRC_PATH), $(SRCS_FILES_EXT))
OBJS 				= 	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:cpp=o))

#		(҂◡_◡)			UTILS			(҂◡_◡)

RM = rm -rf

#		(｡◕‿◕｡)			COLORS			(｡◕‿◕｡)

NONE = \033[0m
HIRED = \033[31m
HIGREEN = \033[92m
HIBLUE = \033[94m
CURSIVE = \033[3m

#		( ಠ ʖ̯ ಠ)		RULES			( ಠ ʖ̯ ಠ)

all: $(NAME)

$(NAME):  $(OBJS)
	@echo "$(HIRED)Compiling ...$(NONE)"
	@ar -rcs $@ $^
	@echo "$(CURSIVE)$(HIGREEN)Done.$(NONE)"

.c.o:
	@$(CC) $(FLAGS) -c ${LIBLINKS} $< -o ${<:.cpp=.o} 


$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} $(LIBLINKS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.phony: all clean fclean re
