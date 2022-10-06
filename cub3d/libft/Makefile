# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 21:47:06 by albaur            #+#    #+#              #
#    Updated: 2022/10/06 16:42:40 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#		( ͡° ͜ʖ ͡°)			COMPILATION			( ͡° ͜ʖ ͡°)

NAME = libft.a
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror
LINKS =
LIBLINKS = -I./includes
SRC_PATH = srcs/
OBJ_PATH = bin/
C_EXTENSION = .c

#		눈_눈			SOURCES			눈_눈

ARR_PATH	=	arr/
ARR_FILES 	= 	ft_arrdup_after ft_arrdup_before ft_arrdup ft_arrjoin \
				ft_arrlen ft_arrndup ft_freearr
SRCS_FILES	+=	$(addprefix $(ARR_PATH), $(ARR_FILES))

ERROR_PATH	=	error/
ERROR_FILES = 	ret_null ret_err throw_error ft_puterror throw_err_ex
SRCS_FILES	+=	$(addprefix $(ERROR_PATH), $(ERROR_FILES))

GNL_PATH	=	gnl/
GNL_FILES 	= 	get_next_line_utils get_next_line
SRCS_FILES	+=	$(addprefix $(GNL_PATH), $(GNL_FILES))

IS_PATH		=	is/
IS_FILES 	= 	ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_isspace
SRCS_FILES	+=	$(addprefix $(IS_PATH), $(IS_FILES))

LST_PATH	=	lst/
LST_FILES 	= 	ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
				ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize
SRCS_FILES	+=	$(addprefix $(LST_PATH), $(LST_FILES))

MEM_PATH	=	mem/
MEM_FILES 	= 	ft_bzero ft_calloc ft_memchr ft_memcmp ft_memcpy ft_memmove \
				ft_memset
SRCS_FILES	+=	$(addprefix $(MEM_PATH), $(MEM_FILES))

PUT_PATH	=	put/
PUT_FILES 	= 	ft_putchar_fd ft_putchar ft_putendl_fd ft_putint_unsigned \
				ft_putnbr_fd ft_putnbr ft_putptr ft_putstr_fd ft_putstr
SRCS_FILES	+=	$(addprefix $(PUT_PATH), $(PUT_FILES))

STR_PATH	=	str/
STR_FILES 	= 	ft_atoi ft_concat ft_dectobin ft_getlastint ft_intlen ft_itoa \
				ft_itohex ft_printf ft_split ft_strcat ft_strchr ft_strcmp \
				ft_strcpy ft_strdup ft_striteri ft_strjoin ft_strlcat \
				ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr \
				ft_strrchr ft_strtololo ft_substr ft_tolower ft_toupper ft_strstr
SRCS_FILES	+=	$(addprefix $(STR_PATH), $(STR_FILES))

SRCS_FILES_EXT 		+= 	$(addsuffix $(C_EXTENSION), $(SRCS_FILES))
SRCS 				+= 	$(addprefix $(SRC_PATH), $(SRCS_FILES_EXT))
OBJS 				= 	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:c=o))

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
			@echo "$(HIRED)Compiling libft...$(NONE)"
			@ar -rcs $@ $^
			@echo "$(HIGREEN)Done.$(NONE)"

.c.o:
	@$(CC) $(FLAGS) -c ${LIBLINKS} $< -o ${<:.c=.o} 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c 
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} $(LIBLINKS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.phony: all clean fclean re
