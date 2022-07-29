# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 17:55:49 by faventur          #+#    #+#              #
#    Updated: 2022/07/22 21:14:27 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_isspace.c ft_strlen.c ft_memset.c ft_bzero.c \
	ft_memalloc.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memdel.c \
	ft_strnew.c ft_strclear.c ft_strdel.c ft_strcpy.c ft_strncpy.c \
	ft_strlcpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_toupper.c \
	ft_tolower.c ft_strchr.c ft_strrchr.c ft_strcmp.c ft_strncmp.c \
	ft_memchr.c ft_memcmp.c ft_strstr.c ft_strnstr.c ft_strequ.c \
	ft_strnequ.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_spacetrim.c ft_split.c ft_itoa.c \
	ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_putchar.c \
	ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putnbr_base.c ft_sort_int_tab.c \
	ft_sort_chartab.c ft_chartab_len.c ft_power.c ft_binary2char.c \
	ft_strtolol.c ft_arr_freer.c ft_arr_freer_index.c ft_puterror.c \
	ft_printf.c ft_printf_basic.c ft_printf_utils.c ft_fprintf.c \
	ft_fprintf_basic.c ft_fprintf_utils.c get_next_line.c ft_arrdup.c \
	ft_arrlen.c ft_arr_display.c ft_arr_display_size.c ft_intarr_freer.c \
	node_del.c

SRCSB	= get_next_line_bonus.c

SRCS_FT	= ft_strstrbool.c ft_strnstrbool.c void_star_cmp.c \
	ft_nodedel.c ft_map_reader.c ft_printerror.c 

SRCS_L	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstsort.c ft_lstmap.c ft_lst_remove_if.c

SRCS_S	= ft_stacknew.c ft_newnode.c ft_stackadd_top.c \
	ft_stackadd_bottom.c ft_stackdelone.c ft_stackclear.c \
	ft_stackinsert.c ft_stackiter.c ft_stacksize.c ft_stacksort.c \
	ft_stackiter_if.c ft_stack_remove_if.c ft_create_chartab.c \
	ft_charr_to_stack_converter.c ft_stacktablen.c ft_stacklen.c

SRCS_Q	= ft_newqueue.c ft_newqelem.c ft_q_init.c ft_enqueue.c \
	ft_dequeue.c ft_q_iter.c

SRCS_BT	= btree_create_node.c btree_apply_prefix.c btree_apply_infix.c \
	btree_apply_suffix.c btree_insert_data.c btree_search_item.c \
	btree_level_count.c ft_btree_clear.c

OBJS	= $(addprefix srcs/, ${SRCS:.c=.o})

OBJSB	= $(addprefix srcsb/, ${SRCSB:.c=.o})

OBJS_FT	= $(addprefix _ft/, ${SRCS_FT:.c=.o})

OBJS_L	= $(addprefix lists/, ${SRCS_L:.c=.o})

OBJS_S	= $(addprefix stacks/, ${SRCS_S:.c=.o})

OBJS_Q	= $(addprefix queues/, ${SRCS_Q:.c=.o})

OBJS_BT	= $(addprefix btrees/, ${SRCS_BT:.c=.o})

NAME	= libft.a

.c.o:
		gcc -Wall -Wextra -Werror -g -c -I./includes $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar -rcs $@ $^

all:		${NAME}

bonus:		${NAME} ${OBJSB}
			ar -rcs ${NAME} ${OBJSB}

_ft:		${NAME} ${OBJS_FT}
			ar -rcs ${NAME} ${OBJS_FT}

lists:		${NAME} ${OBJS_L}
			ar -rcs ${NAME} ${OBJS_L}

stacks:		${NAME} ${OBJS_S}
			ar -rcs ${NAME} ${OBJS_S}

queues:		${NAME} ${OBJS_Q}
			ar -rcs ${NAME} ${OBJS_Q}

btrees:		${NAME} ${OBJS_BT}
			ar -rcs ${NAME} ${OBJS_BT}

clean:
			rm -f ${OBJS} ${OBJSB} ${OBJS_FT} ${OBJS_L} ${OBJS_S} \
				${OBJS_Q} ${OBJS_BT}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re